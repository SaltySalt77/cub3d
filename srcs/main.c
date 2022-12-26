/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:17:09 by hyna              #+#    #+#             */
/*   Updated: 2022/12/26 16:10:17 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perror_exit(void)
{
	perror("Error\n");
	exit(1);
}

int	main(int argc, char	**argv)
{
	t_textures	textures;
	t_info		info;

	if (argc != 2)
	{
		perror("Error\n");
		return (1);
	}
	parser(&textures, &info, argv[1]);
	return (0);
}
