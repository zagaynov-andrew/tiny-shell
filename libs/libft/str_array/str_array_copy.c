/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:19:51 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/10 10:11:54 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

char	**str_array_copy(const char *str_array[])
{
	int		i;
	int		size;
	char	**copy;

	size = (int)str_array_size(str_array);
	copy = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(str_array[i]);
		if (!copy[i])
		{
			str_array_free((char **)str_array);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
