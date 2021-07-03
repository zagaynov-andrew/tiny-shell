/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:28:51 by skharjo           #+#    #+#             */
/*   Updated: 2020/11/06 20:37:36 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i)
	{
		if (str[i] == (char)ch)
			return ((char *)str + i);
		i--;
	}
	if (str[i] == (char)ch)
		return ((char *)str + i);
	return (NULL);
}
