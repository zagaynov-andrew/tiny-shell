/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:13:46 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:02:45 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define STR "-2147483648"

static char	*ft_min_zero(int num)
{
	char	*tmp;
	int		i;

	i = 0;
	if (num == 0)
	{
		tmp = (char *)malloc(sizeof(char) * 2);
		if (!tmp)
			return (NULL);
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = (char *)malloc(sizeof(char) * 12);
	if (tmp)
	{
		while (i < 12)
		{
			tmp[i] = STR[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}

static char	*make_str_from_int(char *c, int sign, int i)
{
	int		k;
	char	*tmp;

	k = 0;
	tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	if (sign < 0)
	{
		tmp[0] = '-';
		k = 1;
	}
	if (tmp)
	{
		while (i > 0)
			tmp[k++] = c[(i--) - 1];
		tmp[k] = '\0';
		return (tmp);
	}
	return (NULL);
}

char	*ft_itoa(int num)
{
	char	c[20];
	int		i;
	char	*tmp;
	int		sign;

	sign = 1;
	i = 0;
	if (num == -2147483648 || num == 0)
		return (ft_min_zero(num));
	if (num < 0)
	{
		num = -num;
		sign = -1;
	}
	while (num > 0)
	{
		c[i++] = num % 10 + 48;
		num = num / 10;
	}
	tmp = make_str_from_int(c, sign, i);
	return (tmp);
}
