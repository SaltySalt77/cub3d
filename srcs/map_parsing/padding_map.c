/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:17:54 by hyna              #+#    #+#             */
/*   Updated: 2022/12/28 16:18:43 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pad_space(char	**temp, t_info	*info, int i)
{
	int	j;
	int	len_origin;

	len_origin = ft_strlen(info->map[i]);
	j = 0;
	while (j < info->max_wid)
	{
		if (j < len_origin)
			temp[i][j] = info->map[i][j];
		else
			temp[i][j] = ' ';
		j++;
	}
	temp[i][j] = 0;
}

int	padding_map(t_info *info)
{
	char	**temp;
	int		i;
	int		len_origin;

	temp = ft_calloc(info->max_hei + 1, sizeof(char *));
	if (!temp)
		perror_exit(NULL);
	i = 0;
	while (info->map[i])
	{
		len_origin = ft_strlen(info->map[i]);
		temp[i] = ft_calloc(info->max_wid + 1, sizeof(char));
		if (!temp[i])
		{
			ft_free_split(temp);
			perror_exit(NULL);
		}
		pad_space(temp, info, i);
		i++;
	}
	temp[i] = 0;
	ft_free_split(info->map);
	info->map = temp;
	return (1);
}
