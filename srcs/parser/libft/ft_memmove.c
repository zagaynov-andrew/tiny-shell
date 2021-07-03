/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:26:53 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:45 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_dst;
	char	*ptr_src;

	ptr_dst = dst;
	ptr_src = (char *)src;
	if (!dst && !src)
		return (0);
	if (ptr_dst < ptr_src)
	{
		while (len--)
			*ptr_dst++ = *ptr_src++;
	}
	else
	{
		while (len > 0)
		{
			*(ptr_dst + (len - 1)) = *(ptr_src + (len - 1));
			len--;
		}
	}
	return (dst);
}
