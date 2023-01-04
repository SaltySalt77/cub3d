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

int	ray_casting(void	*value)
{
	t_data	*m_data;
	t_info	*info;

	m_data = value;
	info = m_data->info;
	///
	t_img buffer; // y-coordinate first because it works per scanline//<<<int*
	buffer.image = mlx_new_image(m_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);


	int pp;
	int xx;
	pp = 0;
	int _ceil = 0;
	int _floor = 0;

	int *buf_address = (int *)mlx_get_data_addr(buffer.image ,&(buffer.bpp),&(buffer.size_l),&(buffer.endian));
	for (int yy = 0; yy < 3; yy++)
	{
		_ceil = _ceil * 256 + m_data->textures.ceiling[yy];
	}
	while(pp < SCREEN_HEIGHT/2)
	{
		xx = 0;
		while(xx < SCREEN_WIDTH)
		{
			buf_address[(buffer.size_l)/4 * pp + xx] = _ceil;
			xx++;
		}
		pp++;
	}
	for (int yy = 0; yy < 3; yy++)//
	{
		_floor = _floor * 256 + m_data->textures.floor[yy];
	}
	while(pp < SCREEN_HEIGHT)
	{
		xx = 0;
		while(xx < SCREEN_WIDTH)
		{
			buf_address[(buffer.size_l)/4 * pp + xx] = _floor;
			xx++;
		}
		pp++;
	}
	int w = SCREEN_WIDTH;
	for(int x = 0; x < w; x++)
	{
		double cameraX = (2*x/(double)w)-1; //x-coordinate in camera space
		double rayDirX = info->dir_x + info->plane_x*cameraX; //planeX
		double rayDirY = info->dir_y + info->plane_y*cameraX; //planeY

		int mapX = (int)info->pos_x;
		int mapY = (int)info->pos_y;

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
			sideDistX = (info->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->pos_y) * deltaDistY;
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
			if (info->map[mapY][mapX] == '1')
			{
				hit = 1;
			}
		}


		if (side == 0) perpWallDist = (mapX - info->pos_x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - info->pos_y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
		double wallX;
		if (side == 0) wallX = info->pos_y + perpWallDist * rayDirY;
		else           wallX = info->pos_x + perpWallDist * rayDirX;
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
			data = (unsigned int *)mlx_get_data_addr(m_data->imgs[text_num].image ,&(m_data->imgs[text_num].bpp),&(m_data->imgs[text_num].size_l),&(m_data->imgs[text_num].endian));
			color = data[(m_data->imgs[text_num].size_l)/4 * texY + texX];//texNum == 0으로 준  상상태
			if(side == 1) color = (color >> 1) & 8355711;
			buf_address[(buffer.size_l)/4 * y + x] = color;
		}
	}
	mlx_put_image_to_window(m_data->mlx, m_data->win, buffer.image, 0, 0);
	mlx_destroy_image(m_data->mlx, buffer.image);
	return (0);
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
		if (!m_data->imgs[i].image)
			perror_exit("No search file or diretory");
		i++;
	}
}

int	release_key(int key_code, t_info *info)
{
	// if (key_code == KEY_ESC)
	// 	exit_game(info);
	if (key_code == KEY_W)
		info->move.w = 0;
	if (key_code == KEY_A)
		info->move.a = 0;
	if (key_code == KEY_S)
		info->move.s = 0;
	if (key_code == KEY_D)
		info->move.d = 0;
	if (key_code == KEY_L)
		info->move.l = 0;
	if (key_code == KEY_R)
		info->move.r = 0;
	return (0);
}

int	press_key(int key_code, t_info *info)
{
	// if (key_code == KEY_ESC)
	// 	exit_game(info);
	if (key_code == KEY_W)
		info->move.w = 1;
	if (key_code == KEY_A)
		info->move.a = 1;
	if (key_code == KEY_S)
		info->move.s = 1;
	if (key_code == KEY_D)
		info->move.d = 1;
	if (key_code == KEY_L)
		info->move.l = 1;
	if (key_code == KEY_R)
		info->move.r = 1;
	return (0);
}

void	key_hook_w(t_info *info)
{
	if (info->map[(int)(info->pos_y + info->dir_y * MOVE_SPEED * 2)][(int)(info->pos_x)] == '0') // 방향 전환 없이 w진행
		info->pos_y += info->dir_y * MOVE_SPEED;
	if (info->map[(int)(info->pos_y)][(int)(info->pos_x + info->dir_x * MOVE_SPEED * 2)] == '0')
		info->pos_x += info->dir_x * MOVE_SPEED;
}

void	key_hook_s(t_info	*info)
{
    if(info->map[(int)(info->pos_y - info->dir_y * MOVE_SPEED * 2)][(int)info->pos_x] == '0')
		info->pos_y -= info->dir_y * MOVE_SPEED;
	if(info->map[(int)info->pos_y][(int)(info->pos_x - info->dir_x * MOVE_SPEED * 2)] == '0')
		info->pos_x -= info->dir_x * MOVE_SPEED;
}

void	key_hook_l(t_info	*info)
{
	double	old_dir;
	double	old_plane;

	old_dir = info->dir_y;
	old_plane = info->plane_y;
	info->dir_y = info->dir_x * sin(-ROT_SPEED) + info->dir_y * cos(-ROT_SPEED);
	info->dir_x = info->dir_x * cos(-ROT_SPEED) - old_dir * sin(-ROT_SPEED);
	info->plane_y = info->plane_x * sin(-ROT_SPEED)
		+ info->plane_y * cos(-ROT_SPEED);
	info->plane_x = info->plane_x * cos(-ROT_SPEED)
		- old_plane * sin(-ROT_SPEED);
}

void	key_hook_r(t_info	*info)
{
	double	old_dir;
	double	old_plane;

	old_dir = info->dir_y;
	old_plane = info->plane_y;
	info->dir_y = info->dir_x * sin(ROT_SPEED) + info->dir_y * cos(ROT_SPEED);
	info->dir_x = info->dir_x * cos(ROT_SPEED) - old_dir * sin(ROT_SPEED);
	info->plane_y = info->plane_x * sin(ROT_SPEED)
		+ info->plane_y * cos(ROT_SPEED);
	info->plane_x = info->plane_x * cos(ROT_SPEED)
		- old_plane * sin(ROT_SPEED);
}

void	key_hook_a(t_info	*info)
{
    if(info->map[(int)(info->pos_y - info->plane_y * MOVE_SPEED * 2)][(int)info->pos_x] == '0')
		info->pos_y -= info->plane_y * MOVE_SPEED;
	if(info->map[(int)info->pos_y][(int)(info->pos_x - info->plane_x * MOVE_SPEED * 2)] == '0')
		info->pos_x -= info->plane_x * MOVE_SPEED;
}
void	key_hook_d(t_info	*info)
{
	if (info->map[(int)(info->pos_y + info->plane_y * MOVE_SPEED * 2)][(int)(info->pos_x)] == '0')
		info->pos_y += info->plane_y * MOVE_SPEED;
	if (info->map[(int)(info->pos_y)][(int)(info->pos_x + info->plane_x * MOVE_SPEED * 2)] == '0')
		info->pos_x += info->plane_x * MOVE_SPEED;
}

int	key_hook(t_info *info)
{
	if (info->move.w && !info->move.s)
		key_hook_w(info);
	if (info->move.s && !info->move.w)
		key_hook_s(info);
	if (info->move.a && !info->move.d)
		key_hook_a(info);
	if (info->move.d && !info->move.a)
		key_hook_d(info);
	if (info->move.l && !info->move.r)
		key_hook_l(info);
	if (info->move.r && !info->move.l)
		key_hook_r(info);
	return (1);
}

int	main_loop(t_data	*m_data)
{
	ray_casting(m_data);
	key_hook(m_data->info);
	return (0);
}

int	main(int argc, char	**argv)
{
	t_info		info;
	t_data		m_data;

	if (argc != 2)
	{
		perror("Error\n");
		system("leaks cub3D");
		return (1);
	}
	//
	info.move.w = 0;
	info.move.a = 0;
	info.move.s = 0;
	info.move.d = 0;
	info.move.l = 0;
	info.move.r = 0;
	//
	parser(&(m_data.textures), &info, argv[1]);
	init_game(&m_data, &(m_data.textures));
	if (!validate_map(&info, argv[1]))
		return (1);
	padding_map(&info);
	check_vec(&info);
	m_data.info = &info;
	////////////////////////////////////////////////
	// double dirX = 0.0, dirY = -1.0; //initial direction vector
	info.dir_x = 0.0;
	info.dir_y = -1.0;
	info.plane_x = 0.66;
	info.plane_y = 0;
	info.map[(int)info.pos_y][(int)info.pos_x] = '0';
	m_data.win = mlx_new_window(m_data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	mlx_hook(m_data.win, X_EVENT_KEY_PRESS, 0, &press_key, &info);
	mlx_hook(m_data.win, X_EVENT_KEY_RELEASE, 0, &release_key, &info);
	mlx_loop_hook(m_data.mlx, &main_loop, (void *)&m_data);
	mlx_loop(m_data.mlx);
	return (0);
}
