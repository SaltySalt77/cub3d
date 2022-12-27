/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:50:51 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 11:50:55 by hyna             ###   ########.fr       */
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