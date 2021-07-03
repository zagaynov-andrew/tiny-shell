/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:40:47 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:33:40 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	char	*str;
	int		i;

	i = number * size;
	str = malloc(i);
	if (str)
	{
		while (i)
		{
			*str++ = 0;
			i--;
		}
	}
	else
		return (NULL);
	return (str - number * size);
}
