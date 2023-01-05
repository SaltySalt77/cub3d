#include "cub3d.h"

int	ray_casting(void	*value)
{
	t_data	*m_data;
	t_info	*info;

	m_data = value;
	info = m_data->info;
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
			if (sideDistX < sideDistY)
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
			color = data[(m_data->imgs[text_num].size_l)/4 * texY + texX];
			buf_address[(buffer.size_l)/4 * y + x] = color;
		}
	}
	mlx_put_image_to_window(m_data->mlx, m_data->win, buffer.image, 0, 0);
	mlx_destroy_image(m_data->mlx, buffer.image);
	return (0);
}
