/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:09:33 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/26 22:17:43 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		size;

	if (!lst)
		return (0);
	size = 1;
	current = lst;
	while (current->next)
	{
		current = current->next;
		size++;
	}
	return (size);
}
