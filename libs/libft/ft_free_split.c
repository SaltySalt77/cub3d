/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:50:51 by hyna              #+#    #+#             */
/*   Updated: 2022/12/28 15:33:09 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_split(char **mem)
{
	int		idx;

	idx = 0;
	if (mem == NULL)
		return (NULL);
	while (mem[idx])
		free(mem[idx++]);
	free(mem);
	return (NULL);
}
