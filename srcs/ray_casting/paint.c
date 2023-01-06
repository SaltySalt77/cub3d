/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:15 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:16 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	init_side_dist(double rayDir, double pos, double *sideDist
	, double deltaDist)
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
