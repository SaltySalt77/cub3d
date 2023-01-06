/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:13 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:10:14 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*find_map(int fd, t_info *info)
{
	char	*compare;

	while (1)
	{
		compare = get_next_line(fd);
		if (!compare
			|| !ft_strncmp(compare, info->map[0], ft_strlen(info->map[0])))
			return (compare);
		free(compare);
	}
}

int	validate_newline(char	*filename, t_info	*info)
{
	char	*compare;
	int		i;
	int		fd;

	i = 0;
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
		return (0);
	compare = find_map(fd, info);
	while (info->map[i])
	{
		if (ft_strncmp(compare, info->map[i], ft_strlen(info->map[i])))
		{
			free(compare);
			close(fd);
			return (0);
		}
		free(compare);
		compare = get_next_line(fd);
		i++;
	}
	free(compare);
	close(fd);
	return (1);
}
