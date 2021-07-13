/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:15:13 by nforce            #+#    #+#             */
/*   Updated: 2021/01/15 16:41:37 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_llitoa(long long int n)
{
	char	*str;
	int		str_len;
	int		negative_flag;

	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	str_len = ft_lli_len(n);
	str = ft_calloc(sizeof(char), str_len + 1);
	if (!str)
		return (NULL);
	str[str_len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		negative_flag = 1;
	}
	else
		negative_flag = 0;
	while ((str_len--) - negative_flag)
	{
		str[str_len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
