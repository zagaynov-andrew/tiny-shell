/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:12:03 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:17:05 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	char			*d;
	const char		*s;
	size_t			n;

	d = dst;
	s = src;
	n = siz;
	if (n != 0)
	{
		while (--n != 0)
		{
			*d++ = *s++;
			if (*d == '\0' || *s == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (siz != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
