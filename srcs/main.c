/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:17:09 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 16:08:35 by nhwang           ###   ########.fr       */
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
	int	i;
	int	wid;
	int	hei;

	i = 0;
	m_data->mlx = mlx_init();
	while (i < 4)
	{
		if (i == 0)
		m_data->imgs[i].image = mlx_xpm_file_to_image(m_data->mlx,
					textures->filename[i], &wid, &hei);
		i++;
	}
	//ㄴㅏ중에 map val >> 이중 str free
	//0 1 ,w s ,,, space는 ok .. 긴 가로 길이 저장
	//padding
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
	vaildate_map(&info, &textures);
	return (0);
}
