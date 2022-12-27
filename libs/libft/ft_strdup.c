/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:04:02 by hyna              #+#    #+#             */
/*   Updated: 2021/11/16 19:10:43 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (0);
	while (i < len)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}
