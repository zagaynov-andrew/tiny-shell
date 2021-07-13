/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:08:40 by nforce            #+#    #+#             */
/*   Updated: 2021/03/27 13:23:09 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_vec.h"

static t_vec	*ft_vec_realloc(t_vec *vec)
{
	void	**new;
	int		i;

	if (!vec)
		return (NULL);
	if (!(new = ft_calloc(vec->capacity * 2, sizeof(void*))))
	{
		i = -1;
		while (++i < (int)vec->size)
			free((vec->data)[i]);
		free(vec->data);
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < (int)vec->size)
	{
		new[i] = (vec->data)[i];
		i++;
	}
	free(vec->data);
	vec->data = new;
	vec->capacity *= 2;
	return (vec);
}

t_vec			*ft_vec_push(t_vec **vec, void *new)
{
	if (!vec)
		return (NULL);
	if ((*vec)->size < (*vec)->capacity)
		((*vec)->data)[(*vec)->size] = new;
	else
	{
		if (!ft_vec_realloc(*vec))
			return (NULL);
		((*vec)->data)[(*vec)->size] = new;
	}
	(*vec)->size++;
	return (*vec);
}
