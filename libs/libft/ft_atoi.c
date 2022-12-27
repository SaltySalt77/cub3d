/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyns@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:25:26 by hyna              #+#    #+#             */
/*   Updated: 2021/11/26 15:41:08 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_space(char	*str)
{
	while ((*str == ' ') || (*str == '\n') || (*str == '\t')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	return (str);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		np;
	int		n;
	long	result;

	str = (char *)nptr;
	np = 1;
	result = 0;
	str = check_space(str);
	if (*str == '-')
	{
		np = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		n = *str - 48;
		result = result * 10 + n;
		str++;
	}
	result = result * np;
	return ((int)result);
}
