/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_env_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 10:48:08 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/10 10:51:13 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_valid_env_name(const char *env_ptr)
{
	int		name_len;
	char	*equal;
	int		i;

	if (ft_isdigit(env_ptr[0]))
		return (0);
	if ((equal = ft_strnstr(env_ptr, "=", ft_strlen(env_ptr))))
		name_len = equal - env_ptr;
	else
		name_len = ft_strlen(env_ptr);
	i = 0;
	while (i < name_len)
	{
		if (!ft_isalnum(env_ptr[i]) && env_ptr[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
