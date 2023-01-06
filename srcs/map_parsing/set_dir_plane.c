/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:06 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:07 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_n(t_info *info)
{
	info->dir_x = 0.0;
	info->dir_y = -1.0;
	info->plane_x = 0.66;
	info->plane_y = 0;
}

void	set_s(t_info *info)
{
	info->dir_x = 0.0;
	info->dir_y = 1.0;
	info->plane_x = -0.66;
	info->plane_y = 0;
}

void	set_e(t_info *info)
{
	info->dir_x = 1.0;
	info->dir_y = 0.0;
	info->plane_x = 0;
	info->plane_y = 0.66;
}

void	set_w(t_info *info)
{
	info->dir_x = -1.0;
	info->dir_y = 0.0;
	info->plane_x = 0;
	info->plane_y = -0.66;
}

void	init_info(t_info *info)
{
	info->move.w = 0;
	info->move.a = 0;
	info->move.s = 0;
	info->move.d = 0;
	info->move.l = 0;
	info->move.r = 0;
	if (info->dir == NORTH)
		set_n(info);
	else if (info->dir == SOUTH)
		set_s(info);
	else if (info->dir == WEST)
		set_w(info);
	else
		set_e(info);
}
