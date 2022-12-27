/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:43:14 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 16:03:49 by hyna             ###   ########.fr       */
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
	info->map[j] = NULL;
	ft_free_split(file);
}
