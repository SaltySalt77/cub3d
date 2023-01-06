/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:09:42 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:09:46 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
