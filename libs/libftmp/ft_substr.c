/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:14:45 by hyna              #+#    #+#             */
/*   Updated: 2021/12/16 22:53:22 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_newlen(char const	*s, size_t	len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len > len)
		return (len);
	return (s_len);
}

char	*ft_substr(char const	*s, unsigned int start, size_t	len)
{
	size_t	pos;
	char	*tmp;

	pos = 0;
	if (!s)
		return (NULL);
	len = ft_newlen(&s[start], len);
	tmp = (char *) ft_calloc((len + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	if (ft_strlen(s) < start)
		return (tmp);
	while ((pos < len) && s[start])
	{
		tmp[pos] = s[start];
		pos++;
		start++;
	}
	return (tmp);
}
