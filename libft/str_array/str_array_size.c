/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:16:34 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/09 23:17:06 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_array.h"

size_t	str_array_size(const char **str_array)
{
	size_t	size;

	size = 0;
	while (str_array[size])
		size++;
	return (size);
}
