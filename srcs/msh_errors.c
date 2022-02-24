/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:35:06 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/19 15:27:10 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exit_error(int ret)
{
	ft_putstr_fd("exit\n", 2);
	return (ret);
}

int	msh_strerror(int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

int	msh_strerror_arg(int ret, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

int	msh_strerror_arg_2(int ret, char *arg_1, char *arg_2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg_1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg_2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}
