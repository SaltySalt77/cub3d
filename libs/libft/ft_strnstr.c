/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyns@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:35:30 by hyna              #+#    #+#             */
/*   Updated: 2021/11/16 17:01:05 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char	*little, size_t	len)
{
	char	*tmpbig;
	char	*tmplittle;
	size_t	i;
	size_t	j;

	tmpbig = (char *) big;
	tmplittle = (char *) little;
	i = 0;
	if (tmplittle[0] == 0)
		return (tmpbig);
	while ((tmpbig[i]) && (i < len))
	{
		j = 0;
		while ((tmpbig[i + j]) && (tmpbig[i + j] == tmplittle[j])
			&& (i + j < len))
		{
			if (tmplittle[j + 1] == 0)
				return (&tmpbig[i]);
			j++;
		}
		i++;
	}
	return (0);
}
