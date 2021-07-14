/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:35:06 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/14 14:58:39 by ngamora          ###   ########.fr       */
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
	return (ret);
}

int	msh_strerror(int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (ret);
}
