/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyns@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:12:35 by hyna              #+#    #+#             */
/*   Updated: 2021/11/17 15:14:26 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (i + 1 < n))
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
