/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:23 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:18:38 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		m_data->imgs[i].addr = (int *) mlx_get_data_addr(m_data->imgs[i].image,
				&m_data->imgs[i].bpp, &m_data->imgs[i].size_l,
				&m_data->imgs[i].endian);
		i++;
	}
}

int	exit_game(t_data *m_data)
{
	mlx_destroy_window(m_data->mlx, m_data->win);
	exit(0);
}
