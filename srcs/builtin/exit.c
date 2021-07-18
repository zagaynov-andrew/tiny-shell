/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:34:29 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 17:43:30 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_number(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	msh_exit(int argc, char *argv[], char *env[])
{
	(void)env;
	if (str_array_size((const char **)argv) > 1)
	{
		if (!is_number(argv[1]))
		{
			ft_putstr_fd("exit\n", 2);
			exit(msh_perror_arg(argv[1], "numeric argument required", 255));
		}
	}
	if (str_array_size((const char **)argv) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		return (msh_perror("exit: too many arguments", 1));
	}
	if (str_array_size((const char **)argv) == 2)
		exit(msh_exit_error(ft_atoi(argv[1]) % 255));
	exit(msh_exit_error(0));
}
