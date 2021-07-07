/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:10:41 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/07 18:13:29 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msh_cd(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	if (argc == 1)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("ERROR"); //
	}
	else if (argc > 2)
	{
		perror("too many arguments"); //
	}
	else
	{
		if (chdir(argv[1]) != 0)
			perror("ERROR"); //
	}
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
//     msh_cd(argc, argv, env);
//     return (0);
// }
