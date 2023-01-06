/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_p_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:09:37 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:09:41 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_key(int key_code, t_data *m_data)
{
	t_info	*info;

	info = m_data->info;
	if (key_code == KEY_ESC)
		exit_game(m_data);
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

int	release_key(int key_code, t_info *info)
{
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
