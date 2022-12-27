/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:49:10 by hyna              #+#    #+#             */
/*   Updated: 2022/12/27 11:49:54 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char	*s1, char *s2)
{
	char	*result;
	size_t	len;
	size_t	s1len;
	size_t	s2len;
	size_t	pos;

	if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	len = s1len + s2len;
	result = (char *) ft_calloc(len + 1, 1);
	if (!result)
		return (0);
	pos = -1;
	while (++pos < s1len)
		result[pos] = s1[pos];
	pos = 0;
	while (pos < s2len)
		result[s1len++] = s2[pos++];
	free(s1);
	free(s2);
	return (result);
}
