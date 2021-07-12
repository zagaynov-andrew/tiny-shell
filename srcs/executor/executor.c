/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:55:31 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/12 20:21:11 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	msh_exec(t_list *cmds, t_list *redirs, char **env[])
{
	int	std_io[2];
	int	ret;

	std_io[0] = dup(0);
	std_io[1] = dup(1);
	ret = msh_simple_cmd_loop(cmds, redirs, std_io, env);
	dup2(std_io[0], 0);
	dup2(std_io[1], 1);
	close(std_io[0]);
	close(std_io[1]);
	return (ret);
}
