/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:21:44 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/15 19:35:52 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

char	**str_array_add_back(char **str_array[], const char *str)
{
	char	**new;
	int		i;
	int		old_size;

	old_size = str_array_size((const char **)(*str_array));
	new = ft_calloc(old_size + 2, sizeof(char *));
	if (!new)
		return (str_array_free(str_array));
	i = 0;
	while (i < old_size)
	{
		new[i] = (char *)(*str_array)[i];
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (str_array_free(str_array));
	new[i + 1] = NULL;
	free(*str_array);
	*str_array = new;
	return (new);
}
