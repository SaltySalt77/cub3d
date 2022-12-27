/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:38:23 by hyna              #+#    #+#             */
/*   Updated: 2021/11/23 16:05:59 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	i = 0;
	if ((s == NULL) || (f == NULL))
		return (NULL);
	result = ft_strdup(s);
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
