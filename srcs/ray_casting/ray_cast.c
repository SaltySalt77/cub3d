/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:18 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:19 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	get_perpwall_dist(int side, double ray_dir_x,
	double ray_dir_y, t_info *info)
{
	if (side == 0)
		return ((info->map_x - info->pos_x + (1 - info->step_x) / 2)
			/ ray_dir_x);
	else
		return ((info->map_y - info->pos_y + (1 - info->step_y) / 2)
			/ ray_dir_y);
}

double	get_wall_x(int side, t_info	*info,
	double perpwall_dist)
{
	double	wall_x;

	if (side == 0)
		wall_x = info->pos_y + perpwall_dist * info->ray_dir_y;
	else
		wall_x = info->pos_x + perpwall_dist * info->ray_dir_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

void	ray_cast(t_data	*m_data, t_info *info, int x)
{
	double	perpwall_dist;
	int		side;
	double	wall_x;
	int		tex_x;
	int		text_num;

	info->ray_dir_x = info->dir_x + info->plane_x
		*((2 * x / (double)SCREEN_WIDTH) - 1);
	info->ray_dir_y = info->dir_y + info->plane_y
		*((2 * x / (double)SCREEN_WIDTH) - 1);
	info->delta_dist_x = sqrt(1 + (info->ray_dir_y * info->ray_dir_y)
			/ (info->ray_dir_x * info->ray_dir_x));
	info->delta_dist_y = sqrt(1 + (info->ray_dir_x * info->ray_dir_x)
			/ (info->ray_dir_y * info->ray_dir_y));
	side = check_hit(info, info->ray_dir_x, info->ray_dir_y);
	perpwall_dist = get_perpwall_dist(side, info->ray_dir_x,
			info->ray_dir_y, info);
	wall_x = get_wall_x(side, info, perpwall_dist);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	text_num = check_texture(info->ray_dir_x, info->ray_dir_y, side);
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
		info->map_x = (int)info->pos_x;
		info->map_y = (int)info->pos_y;
		ray_cast(m_data, info, x);
		x++;
	}
	mlx_put_image_to_window(m_data->mlx, m_data->win, buffer.image, 0, 0);
	mlx_destroy_image(m_data->mlx, buffer.image);
	return (0);
}
