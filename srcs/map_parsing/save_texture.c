/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:02 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:04 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_textures2(t_textures	*textures, int j, char **line)
{
	char	*temp;

	if (j < 4)
	{
		temp = ft_strdup(line[1]);
		if (!temp)
			return (0);
		textures->filename[j] = temp;
		return (1);
	}
	else if (j == FLOOR)
		return (save_rgb(textures->floor, line));
	else
		return (save_rgb(textures->ceiling, line));
}

int	ft_checkline(char **line)
{
	if (ft_strncmp(line[0], "F", 2) && ft_strncmp(line[0], "C", 2))
	{
		if (line[2])
		{
			ft_free_split(line);
			return (0);
		}
		else
			return (1);
	}
	else if (!ft_strncmp(line[0], "F", 2) && count_strs(line) == 4)
		return (1);
	else if (!ft_strncmp(line[0], "C", 2) && count_strs(line) == 4)
		return (1);
	ft_free_split(line);
	return (0);
}

void	init_vars(char	*std[6], int chk[6])
{
	std[NORTH] = "NO";
	std[SOUTH] = "SO";
	std[WEST] = "WE";
	std[EAST] = "EA";
	std[FLOOR] = "F";
	std[CEILING] = "C";
	ft_bzero(chk, 6 * (sizeof(int)));
}

int	verify_idf(char	**file, char	**line, char	*std[6], int	*chk)
{
	int		j;

	j = -1;
	while (++j < 6)
	{
		if (!ft_strncmp(line[0], std[j], ft_strlen(std[j])))
		{
			if (chk[j] || ft_strlen(line[0]) != ft_strlen(std[j]))
			{
				ft_free_split(file);
				ft_free_split(line);
				perror_exit("Invalid identifier");
			}
			chk[j] = 1;
			break ;
		}
	}
	if (j >= 6)
	{
		ft_free_split(file);
		ft_free_split(line);
		perror_exit("Invalid identifier");
	}
	return (j);
}

void	assort_textures(char **file, t_textures	*textures, char	*std[6])
{
	char	**line;
	int		cnt;
	int		chk[6];
	int		i;

	i = -1;
	cnt = 0;
	init_vars(std, chk);
	while (file[++i] && cnt < 6 && cnt == i)
	{
		line = ft_split2(file[i], " ,");
		if (!line || count_strs(line) < 2 || !ft_checkline(line))
		{
			ft_free_split(file);
			perror_exit("Invalid identifier");
		}
		cnt += (save_textures2(textures,
					verify_idf(file, line, std, chk), line));
		ft_free_split(line);
	}
	if (cnt != 6)
	{
		ft_free_split(file);
		perror_exit("Invalid identifier");
	}
}
