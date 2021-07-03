/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:23:34 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:39 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	const char	*tsrc;
	char		*tdest;

	tsrc = srcptr;
	tdest = destptr;
	if (!tsrc && !tdest)
		return (0);
	while (num--)
	{
		*tdest++ = *tsrc++;
	}
	return (destptr);
}
