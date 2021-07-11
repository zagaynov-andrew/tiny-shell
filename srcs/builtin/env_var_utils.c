/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 10:48:08 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/11 13:30:29 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_valid_env_name(const char *env_ptr)
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

int	get_env_pos(const char *name, const char **env)
{
	int		i;
	int		cur_name_len;
	int		name_len;
	char	*equal;

	if ((equal = ft_strnstr(name, "=", ft_strlen(name))))
		name_len = equal - name;
	else
		name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((equal = ft_strnstr(env[i], "=", ft_strlen(env[i]))))
			cur_name_len = equal - env[i];
		else
			cur_name_len = ft_strlen(env[i]);
		if (name_len == cur_name_len
					&& ft_strncmp(env[i], name, cur_name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
