/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:21:07 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/14 16:50:28 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_lst_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**array;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	array = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		array[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
