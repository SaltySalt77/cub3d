/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:09:51 by hyna              #+#    #+#             */
/*   Updated: 2023/01/06 12:09:53 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cut_map(char	**file, t_info	*info)
{
	int	cnt;
	int	i;
	int	j;

	cnt = count_strs(&(file[6]));
	info->map = malloc(sizeof(char *) * (cnt + 1));
	if (!info->map)
	{
		ft_free_split(file);
		return ;
	}
	i = 5;
	j = -1;
	while (file[++i])
	{
		info->map[++j] = ft_strdup(file[i]);
		if (!info->map[j])
		{
			ft_free_split(file);
			info->map = ft_free_split(info->map);
			return ;
		}
	}
	info->map[++j] = NULL;
	ft_free_split(file);
}
