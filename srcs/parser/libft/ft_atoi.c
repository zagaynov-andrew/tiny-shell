/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:36:10 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:31:13 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	if_sign(char ch)
{
	if (ch == '-')
		return (-1);
	return (1);
}

int	if_over(int sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				sign;
	int				nbr;
	long long int	llval;
	long long int	tmp;

	sign = 1;
	nbr = 0;
	llval = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		sign = if_sign(*str);
	str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		tmp = llval;
		llval = llval * 10 + (*str++ - 48);
		if (tmp > llval)
			return (if_over(sign));
	}
	return (nbr * sign);
}
