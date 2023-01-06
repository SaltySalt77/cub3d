/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:10 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:11 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_c(char c, int chk_dir)
{
	if (c == '0' || c == '1' || c == ' ')
		return (2);
	if ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'))
	{
		if (chk_dir)
			return (0);
		return (1);
	}
	return (0);
}

void	save_chara_dir(t_info	*info, int	*chk_dir, int i, int j)
{
	char	dir;

	info->pos_x = j + 0.5;
	info->pos_y = i + 0.5;
	dir = info->map[i][j];
	if (dir == 'N')
		info->dir = 0;
	else if (dir == 'S')
		info->dir = 1;
	else if (dir == 'E')
		info->dir = 3;
	else if (dir == 'W')
		info->dir = 2;
	*chk_dir = 1;
}

int	count_map(char **map, t_info *info)
{
	int	i;
	int	j;
	int	chk_dir;

	info->max_wid = 0;
	i = 0;
	chk_dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_c(map[i][j], chk_dir) == 1)
				save_chara_dir(info, &chk_dir, i, j);
			else if (!check_c(map[i][j], chk_dir))
				return (0);
			j++;
		}
		if (j > info->max_wid)
			info->max_wid = j;
		i++;
	}
	info->max_hei = i;
	return (chk_dir);
}

int	validate_map(t_info *info, char	*filename)
{
	if (!count_map(info->map, info))
		perror_exit("Invalid map element");
	if (!validate_newline(filename, info))
		perror_exit("Invalid map");
	return (1);
}

void	check_fc(char **file)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	while (file[i])
	{
		if (file[i][0] == 'C' || file[i][0] == 'F')
		{
			cnt = 0;
			j = 0;
			while (file[i][j])
			{
				if (file[i][j] == ',')
					cnt++;
				j++;
			}
			if (cnt > 2)
				perror_exit("Invaild identifier");
		}
		i++;
	}
}
