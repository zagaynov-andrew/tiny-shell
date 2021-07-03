/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:32:35 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:35:51 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int		i;
	char				*memory;

	memory = str;
	i = 0;
	while (i < n)
	{
		memory[i] = c;
		i++;
	}
	return (memory);
}
