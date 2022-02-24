/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:57:45 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/14 16:14:25 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	const char	endl = '\n';
	int			total;

	total = 0;
	if (!s)
		return (write(fd, &endl, 1));
	total += (int)write(fd, s, ft_strlen(s));
	total += (int)write(fd, &endl, 1);
	return (total);
}
