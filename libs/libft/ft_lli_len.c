/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lli_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:59:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/15 16:00:19 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lli_len(long long int n)
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
