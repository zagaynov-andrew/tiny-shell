/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 21:08:20 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/07 18:13:42 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msh_env(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	while (*env)
	{
		printf("%s\n", *env);
		(*env)++;
	}
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_env(argc, argv, env);
// 	return (0);
// }
