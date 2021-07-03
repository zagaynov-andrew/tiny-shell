/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:19:48 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:28 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memptr, int val, size_t num)
{
	const char	*tmp;
	const char	*tmem;
	size_t		i;

	i = 0;
	tmem = memptr;
	while (i < num)
	{
		if (tmem[i] == (char)val)
		{
			tmp = &tmem[i];
			return ((void *)tmp);
		}
		i++;
	}
	return (NULL);
}
