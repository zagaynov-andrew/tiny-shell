/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:10:16 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/15 19:47:42 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

char	**str_array_free(char **str_array[])
{
	int	i;

	if (!*str_array)
		return (NULL);
	i = 0;
	while ((*str_array)[i])
	{
		free((*str_array)[i]);
		i++;
	}
	free(*str_array);
	*str_array = NULL;
	return (NULL);
}
