/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:05:29 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/06 23:01:42 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msh_pwd(int argc, char *argv[], char *env[])
{
	(void)argc;
    (void)argv;
    (void)env;
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] != '\0') // check -, --, -dafb, -s 
		{
			perror("-q: invalid option"); //
			return (0);
		}
		else if (argv[1][0] == '-' && argv[1][1] != '\0' && argv[1][1] != '-') // check -, --, -dafb, -s 
		{
			perror("-q: invalid option"); //
			return (0);
		}
	}
	printf("%s\n", getenv("PWD"));
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_pwd(argc, argv, env);
// 	return (0);
// }