/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:48:07 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/17 22:06:40 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ilen(int n)
{
	int	str_len;

	if (n == 0)
		return (1);
	str_len = 0;
	if (n < 0)
		str_len++;
	while (n)
	{
		str_len++;
		n /= 10;
	}
	return (str_len);
}

static char	*ft_itoa_min(void)
{
	char	*str;

	str = ft_calloc(12, sizeof(char));
	ft_strlcpy(str, "-2147483648", 12);
	if (!str)
		return (NULL);
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		str_len;
	int		negative_flag;

	if (n == -2147483648)
		return (ft_itoa_min());
	str_len = ft_ilen(n);
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
