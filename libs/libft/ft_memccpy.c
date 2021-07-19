/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:26:24 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/17 21:48:01 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	*dst_uc;
	unsigned char	*src_uc;

	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	i = 0;
	while (i < (int)n)
	{
		dst_uc[i] = src_uc[i];
		if (src_uc[i] == (unsigned char)c)
			return (dst_uc + i + 1);
		i++;
	}
	return (NULL);
}
