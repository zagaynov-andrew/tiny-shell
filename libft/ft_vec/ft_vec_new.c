/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:20:22 by nforce            #+#    #+#             */
/*   Updated: 2021/03/27 10:19:14 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_vec.h"

t_vec	*ft_vec_new(size_t capacity)
{
	t_vec	*vec;

	if (!capacity)
		return (NULL);
	if (!(vec = ft_calloc(capacity, sizeof(t_vec))))
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (!(vec->data = ft_calloc(capacity, sizeof(void*))))
	{
		errno = ENOMEM;
		return (NULL);
	}
	vec->size = 0;
	vec->capacity = capacity;
	return (vec);
}
