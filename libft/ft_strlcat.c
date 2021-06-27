/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:51:20 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/17 21:48:38 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int	src_len;
	int	dst_len;
	int	i;
	int j;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if ((int)dstsize - 1 < dst_len)
		return (src_len + (int)dstsize);
	i = dst_len;
	j = 0;
	while (i < (src_len + dst_len) && i < (int)dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
