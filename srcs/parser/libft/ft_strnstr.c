/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:18:43 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:00:24 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lit_len;

	lit_len = 0;
	lit_len = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (*big && len >= lit_len)
	{
		if (!ft_strncmp(little, big, lit_len) && *little == *big)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
