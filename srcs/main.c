/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:17:09 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 14:44:46 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perror_exit(void)
{
	perror("Error\n");
	exit(1);
}

void	init_game(t_data *m_data, t_textures *textures)
{
	m_data->mlx = mlx_init();
	m_data->imgs[]
	// m_data->win =
}

int	main(int argc, char	**argv)
{
	t_textures	textures;
	t_info		info;
	t_data		m_data;

	if (argc != 2)
	{
		perror("Error\n");
		return (1);
	}
	parser(&textures, &info, argv[1]);
	init_game(&m_data, &textures);
	return (0);
}
