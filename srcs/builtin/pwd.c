/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:05:29 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/12 18:19:00 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_cur_dir(void)
{
	int		size;
	char	*path;
	char	*tmp;

	size = 64;
	path = (char *)ft_calloc(size, sizeof(char));
	if (!path)
		return (NULL);
	tmp = path;
	path = getcwd(path, size);
	if (!path && errno != 34)
		return (path);
	while (!path)
	{
		free(tmp);
		size *= 2;
		path = (char *)ft_calloc(size, sizeof(char));
		if (!path)
			return (NULL);
		path = getcwd(path, size);
		if (!path && errno != 34)
			return (path);
	}
	errno = 0;
	return (path);
}

int	msh_pwd(int argc, char *argv[], char *env[])
{
	char	*cur_dir;
	(void)env;
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == '-'
			&& argv[1][2] != '\0') // check -, --, -dafb, -s
		{
			ft_putstr_fd("minishell: pwd: -", 2);
			ft_putchar_fd(argv[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
		else if (argv[1][0] == '-' && argv[1][1] != '\0'
			&& argv[1][1] != '-') // check -, --, -dafb, -s
		{
			ft_putstr_fd("minishell: pwd: -", 2);
			ft_putchar_fd(argv[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
	}
	cur_dir = get_cur_dir();
	if (!cur_dir)
		return (1);
	ft_putstr_fd(cur_dir, 1);
	ft_putchar_fd('\n', 1);
	free(cur_dir);
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_pwd(argc, argv, env);
// 	return (0);
// }
