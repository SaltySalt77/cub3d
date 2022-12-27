/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyns@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:24:28 by hyna              #+#    #+#             */
/*   Updated: 2021/12/09 15:20:16 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	tmp;
	int		pos;

	pos = (int) ft_strlen(s);
	tmp = (char) c;
	while ((pos >= 0) && (s[pos] != tmp))
		pos--;
	if (pos == -1)
		return (NULL);
	return ((char *) &s[pos]);
}
