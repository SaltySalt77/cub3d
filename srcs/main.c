/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:17:09 by hyna              #+#    #+#             */
/*   Updated: 2022/12/28 11:20:52 by hyna             ###   ########.fr       */
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
	if (!validate_map(&info, &textures, argv[1]))
		return (1);
	printf("=========\n"); //
	padding_map(&info);
	for (int i = 0; info.map[i]; i++)
		printf("%s | \n",info.map[i]);
	return (0);
}
