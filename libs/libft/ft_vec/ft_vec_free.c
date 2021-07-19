/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:10:00 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 13:52:49 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_vec.h"

void	ft_vec_data_free(void **data, size_t size)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < (int)size)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	ft_vec_free(t_vec *vec)
{
	if (!vec)
		return ;
	ft_vec_data_free(vec->data, vec->size);
	free(vec);
}
