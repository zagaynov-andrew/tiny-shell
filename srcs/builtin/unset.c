/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 01:12:51 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/19 15:24:00 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msh_unset(const int argc, const char *argv[], char **env[])
{
	int	i;
	int	flag;
	int	pos;

	flag = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_valid_env_name(argv[i]))
		{
			print_not_valid(argv[i]);
			flag = 1;
			i++;
			continue ;
		}
		pos = get_env_pos(argv[i], (const char **)*env);
		if (pos >= 0)
			if (!str_array_erase(env, pos))
				return (1);
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

// int		main(const int argc, const char *argv[], char *env[])
// {
// 	char	**copy_env;
// 	print_str_array(env);
// 	printf("\n\n\n");
// 	copy_env = str_array_copy((const char **)env);
// 	// copy_env = str_array_add_back(&copy_env, "first=string");
// 	// copy_env = str_array_add_back(&copy_env, "second=string");
// 	// copy_env = str_array_add_back(&copy_env, "third=string");
// 	// copy_env = str_array_add_back(&copy_env, "forth=string");

// 	msh_unset(argc, argv, &copy_env);
// 	print_str_array(copy_env);
// 	str_array_free(copy_env);
// 	// char    **arr = NULL;
// 	// arr = str_array_add_back(&arr, "first=string");
// 	// arr = str_array_add_back(&arr, "second=string");
// 	// arr = str_array_add_back(&arr, "third=string");
// 	// arr = str_array_add_back(&arr, "forth=string");
// 	// arr = str_array_erase(&arr, 1);
// 	// // arr = str_array_erase(&arr, 0);
// 	// // arr = str_array_erase(&arr, 0);
// 	// print_str_array(arr);
// 	// str_array_free(arr);
// 	return (0);
// }
