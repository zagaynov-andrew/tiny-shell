/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:17:42 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/10 10:11:37 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

static void	str_swap(char **str_1, char **str_2)
{
	char	*tmp;

	tmp = *str_1;
	*str_1 = *str_2;
	*str_2 = tmp;
}

char		**str_array_sort(char *str_array[])
{
	int	i;
	int	j;
	int	size;

	size = (int)str_array_size((const char **)str_array);
	j = 1;
	while (j < size)
	{
		i = 0;
		while (i < size - j)
		{
			if (ft_strcmp(str_array[i], str_array[i + 1]) > 0)
				str_swap(&str_array[i], &str_array[i + 1]);
			i++;
		}
		j++;
	}
	return (str_array);
}
