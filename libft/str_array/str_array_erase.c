/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_erase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 00:59:10 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/10 10:22:49 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

static char	**str_array_erase_utils(char **str_array[], char *new[], int pos, int old_size)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < old_size)
	{
		if (i != pos)
		{
			new[i - flag] = (*str_array)[i];
			if (!new[i - flag])
			{
				str_array_free((char **)(*str_array));
				return (NULL);
			}
		}
		else
		{
			free((*str_array)[i]);
			flag = 1;
		}
	}
	new[i - flag] = NULL;
	return (new);
}

char		**str_array_erase(char **str_array[], int pos)
{
	char	**new;
	int		old_size;

	if (!str_array)
		return (NULL);
	old_size = (int)str_array_size((const char **)(*str_array));
	if (pos >= old_size)
		return (NULL);
	new = (char **)ft_calloc(old_size, sizeof(char *));
	if (!new)
		return (NULL);
	
	if (!str_array_erase_utils(str_array, new, pos, old_size))
		return (NULL);
	free(*str_array);
	*str_array = new;
	return (new);
}
