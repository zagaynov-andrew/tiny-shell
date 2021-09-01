/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:56:00 by nforce            #+#    #+#             */
/*   Updated: 2021/07/14 16:32:19 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int value, int base)
{
	char			*str;
	size_t			size;
	char			*alphabit;
	long long int	tmp;

	size = 0;
	alphabit = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (NULL);
	tmp = value / base;
	while (tmp)
	{
		size++;
		tmp /= base;
	}
	size++;
	str = (char *)ft_calloc(size + 1, sizeof(char));
	str[size] = '\0';
	while (size)
	{
		str[size - 1] = alphabit[ft_abs(value % base)];
		size--;
		value /= base;
	}
	return (str);
}
