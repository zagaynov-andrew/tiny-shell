/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:33:23 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/12 11:51:57 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	msh_export_print(const char **str_array)
{
	int	i;
	int	j;

	i = 0;
	while (str_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (str_array[i][j] != '=' && str_array[i][j] != '\0')
		{
			ft_putchar_fd(str_array[i][j], 1);
			j++;
		}
		if (str_array[i][j] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(&str_array[i][j + 1], 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	msh_export_add_env(const char *argv[], char **env[])
{
	int		i;
	int		pos;
	int		flag;

	flag = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_env_name(argv[i]))
		{
			flag = 1;
			i++;
			continue ;
		}
		if ((pos = get_env_pos(argv[i], (const char **)*env)) >= 0)
		{
			if (ft_strnstr(argv[i], "=", ft_strlen(argv[i])))
			{
				free((char *)(*env)[pos]);
				(*env)[pos] = ft_strdup(argv[i]);
			}
		}
		else
		{
			if (!(*env = str_array_add_back(env, argv[i])))
			{
				perror("ERROR"); //
				return (errno);
			}
		}
		i++;
	}
	if (flag)
	{
		perror("ERROR not a valid identifier"); //
		return (1);
	}
	return (0);
}

int	msh_export(const int argc, const char *argv[], char **env[])
{
	char	**copy;

	if (argc == 1)
	{
		if (!(copy = str_array_copy((const char **)*env)))
			return (errno);
		str_array_sort(copy);
		msh_export_print((const char **)copy);
		str_array_free(copy);
		return (0);
	}
	else
		return (msh_export_add_env(argv, env));
}

// int		main(const int argc, const char *argv[], char *env[])
// {
// 	msh_export_print((const char **)env);
// 	char	**copy_env;
// 	copy_env = str_array_copy((const char **)env);
// 	// copy_env = NULL;
// 	// copy_env = str_array_add_back(&copy_env, "first=string");
// 	// copy_env = str_array_add_back(&copy_env, "second=string");
// 	// copy_env = str_array_add_back(&copy_env, "third=string");
// 	// copy_env = str_array_add_back(&copy_env, "forth=string");
// 	msh_export_print((const char **)copy_env);
// 	msh_export(argc, argv, &copy_env);
// 	msh_export_print((const char **)copy_env);
// 	str_array_free(copy_env);
// 	return (0);
// }
