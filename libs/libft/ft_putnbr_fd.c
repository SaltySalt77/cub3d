/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:23:12 by hyna              #+#    #+#             */
/*   Updated: 2021/11/23 16:32:26 by hyna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_num(int n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + 48;
		write(fd, &c, 1);
	}
	else
	{
		print_num(n / 10, fd);
		print_num(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
		{
			n = -n;
			write(fd, "-", 1);
		}
		print_num(n, fd);
	}
}
