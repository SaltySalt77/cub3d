#include "cub3d.h"

void	painter(t_img *buffer, int _ceil, int _floor)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			buffer->addr[(buffer->size_l) / 4 * y + x] = _ceil;
			buffer->addr[(buffer->size_l) / 4 * (SCREEN_HEIGHT - y - 1) + x]
				= _floor;
			x++;
		}
		y++;
	}
}

void	paint_back(t_data *m_data, t_img *buffer)
{
	int	_ceil;
	int	_floor;
	int	temp;

	buffer->image = mlx_new_image(m_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	_ceil = 0;
	_floor = 0;
	buffer->addr = (int *)mlx_get_data_addr(buffer->image,
			&(buffer->bpp), &(buffer->size_l), &(buffer->endian));
	temp = -1;
	while (++temp < 3)
	{
		_ceil = _ceil * 256 + m_data->textures.ceiling[temp];
		_floor = _floor * 256 + m_data->textures.floor[temp];
	}
	painter(buffer, _ceil, _floor);
}

int	init_side_dist(double rayDir, double pos, double *sideDist, double deltaDist)
{
	int	step;

	if (rayDir < 0)
	{
		step = -1;
		*sideDist = pos * deltaDist;
	}
	else
	{
		step = 1;
		*sideDist = (-pos + 1.0) * deltaDist;
	}
	return (step);
}

int	check_hit(t_info *info, double rayDirX, double rayDirY)
{
	int	side;

	info->step_x = init_side_dist(rayDirX, info->pos_x - (int)info->pos_x,
			&(info->side_dist_x), info->delta_dist_x);
	info->step_y = init_side_dist(rayDirY, info->pos_y - (int)info->pos_y,
			&(info->side_dist_y), info->delta_dist_y);
	while (1)
	{
		if (info->side_dist_x < info->side_dist_y)
		{
			info->side_dist_x += info->delta_dist_x;
			info->map_x += info->step_x;
			side = 0;
		}
		else
		{
			info->side_dist_y += info->delta_dist_y;
			info->map_y += info->step_y;
			side = 1;
		}
		if (info->map[info->map_y][info->map_x] == '1')
			break ;
	}
	return (side);
}

int	check_texture(double rayDirX, double rayDirY, int side)
{
	int	text_num;

	if (rayDirX < 0 && side == 0)
		text_num = WEST;
	else if (rayDirX > 0 && side == 0)
		text_num = EAST;
	else if (rayDirY < 0 && side == 1)
		text_num = NORTH;
	else
		text_num = SOUTH;
	return (text_num);
}

void	draw_line(t_data *m_data, int text_num, int lineHeight, int x)
{
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
	int		y;

	draw_start = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	step = 1.0 * TEX_WIDTH / lineHeight;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		m_data->imgs[text_num].tex_y = (int)tex_pos & (TEX_WIDTH - 1);
		tex_pos += step;
		m_data->img_buff->addr[(m_data->img_buff->size_l) / 4 * y + x]
			= m_data->imgs[text_num].addr[(m_data->imgs[text_num].size_l) / 4
			* m_data->imgs[text_num].tex_y + m_data->imgs[text_num].tex_x];
		y++;
	}
}

void	ray_cast(t_data	*m_data, t_info *info, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perpwall_dist;
	int		side;
	double	wall_x;
	int		tex_x;
	int		text_num;

	camera_x = (2 * x / (double)SCREEN_WIDTH) - 1;
	ray_dir_x = info->dir_x + info->plane_x * camera_x;
	ray_dir_y = info->dir_y + info->plane_y * camera_x;
	info->map_x = (int)info->pos_x;
	info->map_y = (int)info->pos_y;
	info->delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	info->delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
	side = check_hit(info, ray_dir_x, ray_dir_y);
	if (side == 0)
		perpwall_dist = (info->map_x - info->pos_x + (1 - info->step_x) / 2) / ray_dir_x;
	else
		perpwall_dist = (info->map_y - info->pos_y + (1 - info->step_y) / 2) / ray_dir_y;
	if (side == 0)
		wall_x = info->pos_y + perpwall_dist * ray_dir_y;
	else
		wall_x = info->pos_x + perpwall_dist * ray_dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	text_num = check_texture(ray_dir_x, ray_dir_y, side);
	if (text_num == SOUTH || text_num == WEST)
		tex_x = TEX_WIDTH - tex_x - 1;
	m_data->imgs[text_num].tex_x = tex_x;
	draw_line(m_data, text_num, (int)(SCREEN_HEIGHT / perpwall_dist), x);
}

int	ray_casting(void	*value)
{
	t_data	*m_data;
	t_info	*info;
	int		x;
	t_img	buffer;

	m_data = value;
	info = m_data->info;
	paint_back(m_data, &buffer);
	m_data->img_buff = &buffer;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_cast(m_data, info, x);
		x++;
	}
	mlx_put_image_to_window(m_data->mlx, m_data->win, buffer.image, 0, 0);
	mlx_destroy_image(m_data->mlx, buffer.image);
	return (0);
}
