/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyns@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:14:14 by hyna              #+#    #+#             */
/*   Updated: 2021/11/26 15:26:06 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy(unsigned char	*tmpdest, unsigned char	*tmpsrc, size_t	n)
{
	size_t	pos;

	if (tmpdest < tmpsrc)
	{
		pos = 0;
		while (pos < n)
		{
			tmpdest[pos] = tmpsrc[pos];
			pos++;
		}
	}
	else
	{
		pos = n;
		while (pos)
		{
			tmpdest[pos - 1] = tmpsrc[pos - 1];
			pos--;
		}
	}
}

void	*ft_memmove(void	*dest, const void	*src, size_t	n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	if (!dest && !src)
		return (NULL);
	tmpdest = (unsigned char *) dest;
	tmpsrc = (unsigned char *) src;
	copy(tmpdest, tmpsrc, n);
	return (dest);
}
