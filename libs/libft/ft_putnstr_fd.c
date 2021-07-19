/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:00:20 by nforce            #+#    #+#             */
/*   Updated: 2021/01/14 16:12:56 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnstr_fd(char *s, size_t len, int fd)
{
	int	slen;
	int	total;

	total = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if ((int)len > slen)
	{
		total += (int)write(fd, s, ft_strlen(s));
		return (total);
	}
	else
	{
		total += (int)write(fd, s, len);
		return (total);
	}
}
