#include "cub3d.h"

void	perror_exit(char *err_msg)
{
	if (!err_msg)
	{
		perror("Error\n");
		exit(1);
	}
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	system("leaks cub3D | grep leaks");
	exit(1);
}

void	init_game(t_data *m_data, t_textures *textures)
{
	int	i;
	int	wid;
	int	hei;

	i = 0;
	m_data->mlx = mlx_init();
	while (i < 4)
	{
		m_data->imgs[i].image = mlx_xpm_file_to_image(m_data->mlx,
					textures->filename[i], &wid, &hei);
		printf("%s\n", textures->filename[i]);
		if (!m_data->imgs[i].image)
			perror_exit("No search file or diretory");
		i++;
	}
}

int	main(int argc, char	**argv)
{
	t_textures	textures;
	t_info		info;
	t_data		m_data;

	if (argc != 2)
	{
		perror("Error\n");
		system("leaks cub3D");
		return (1);
	}
	parser(&textures, &info, argv[1]);
	init_game(&m_data, &textures);
	if (!validate_map(&info, argv[1]))
		return (1);
	padding_map(&info);
	for (int i = 0; info.map[i]; i++)
		printf("%s | \n",info.map[i]);
	check_vec(&info);
	////////////////////////////////////////////////
	// double dirX = 0.0, dirY = -1.0; //initial direction vector
	info.dir_x = 0.0;
	info.dir_y = -1.0;
	double planeX = 0.66, planeY = 0.0; //the 2d raycaster version of camera plane
	m_data.win = mlx_new_window(m_data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");

	t_img buffer; // y-coordinate first because it works per scanline//<<<int*
	buffer.image = mlx_new_image(m_data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	int *buf_address = (int *)mlx_get_data_addr(buffer.image ,&(buffer.bpp),&(buffer.size_l),&(buffer.endian));
	int w = SCREEN_WIDTH;
	printf("first dir : %lf\n",info.dir_x);
	printf("first dir : %lf\n",info.dir_y);

	while(1)
  	{
		for(int x = 0; x < w; x++)
		{
			double cameraX = (2*x/(double)w)-1; //x-coordinate in camera space
			double rayDirX = info.dir_x + planeX*cameraX;
			double rayDirY = info.dir_y + planeY*cameraX;

			int mapX = (int)info.pos_x;
			int mapY = (int)info.pos_y;

			double sideDistX;
			double sideDistY;

			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?

			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (info.pos_x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - info.pos_x) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (info.pos_y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - info.pos_y) * deltaDistY;
			}
			while (hit == 0)
			{
				if (sideDistX < sideDistY)// <
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (info.map[mapY][mapX] == '1')
				{
					hit = 1;
				}
			}
			if (side == 0) perpWallDist = (mapX - info.pos_x + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - info.pos_y + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
			printf("----------%d----------\n", lineHeight);
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
			if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
			double wallX;
			if (side == 0) wallX = info.pos_y + perpWallDist * rayDirY;
			else           wallX = info.pos_x + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			int texX = (int)(wallX * (double)TEX_WIDTH);

			int	text_num;

			if (rayDirX < 0 && side == 0)
				text_num = WEST;
			else if (rayDirX > 0 && side == 0)
				text_num = EAST;
			else if (rayDirY < 0 && side == 1)
				text_num = NORTH;
			else
				text_num = SOUTH;
			// 조건문 texture 선택, 벽의 방향 기준
			if(rayDirX < 0 && side == 0) texX = TEX_WIDTH - texX - 1;//0 // west texture
			if(rayDirY > 0 && side == 1) texX = TEX_WIDTH - texX - 1;//1 // south texture
			double step = 1.0 * TEX_WIDTH / lineHeight;
			double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
			unsigned int *data;
			int color;
			for(int y = drawStart; y<drawEnd; y++)
			{
				int texY = (int)texPos & (TEX_WIDTH - 1);
				texPos += step;
				data = (unsigned int *)mlx_get_data_addr(m_data.imgs[text_num].image ,&(m_data.imgs[text_num].bpp),&(m_data.imgs[text_num].size_l),&(m_data.imgs[text_num].endian));
				color = data[(m_data.imgs[text_num].size_l)/4 * texY + texX];//texNum == 0으로 준  상상태
				printf("%d, %d\n",texY,texX);
				if(side == 1) color = (color >> 1) & 8355711;
				buf_address[(buffer.size_l)/4 * y + x] = color;
				printf("%d, %d\n",y,x);
				printf("\n");
			}
		}
		mlx_put_image_to_window(m_data.mlx, m_data.win, buffer.image, 0, 0);
		break ;
	}
	mlx_loop(m_data.mlx);
	return (0);
}
