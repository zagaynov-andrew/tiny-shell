/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:04:19 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/14 16:14:57 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		total;

	total = 0;
	if (n == -2147483648)
		return ((int)write(fd, "-2147483648", 11));
	if (n < 0)
	{
		total += (int)write(fd, "-", 1);
		total += (int)ft_putnbr_fd(-n, fd);
	}
	else if (n <= 9)
	{
		c = n + '0';
		total += (int)write(fd, &c, 1);
	}
	else
	{
		total += (int)ft_putnbr_fd(n / 10, fd);
		c = n % 10 + '0';
		total += (int)write(fd, &c, 1);
	}
	return (total);
}
