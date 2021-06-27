/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:26:41 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/18 16:43:31 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*dst_uc;
	unsigned char	*src_uc;

	if (!dst && !src)
		return (NULL);
	i = 0;
	dst_uc = (unsigned char*)dst;
	src_uc = (unsigned char*)src;
	if (dst < src)
		while (i < (int)len)
		{
			dst_uc[i] = src_uc[i];
			i++;
		}
	else
	{
		while (len--)
			dst_uc[len] = src_uc[len];
	}
	return (dst);
}
