/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:26:41 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/19 15:27:15 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_perror(char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

int	msh_perror_arg(char *arg, char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}
