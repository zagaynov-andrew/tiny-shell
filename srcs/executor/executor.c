/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:55:31 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/16 13:40:48 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	msh_exec(t_list *cmds, t_list *redirs, char **env[])
{
	int	std_io[2];

	std_io[0] = dup(0);
	std_io[1] = dup(1);
	msh_simple_cmd_loop(cmds, redirs, std_io, env);
	dup2(std_io[0], 0);
	dup2(std_io[1], 1);
	close(std_io[0]);
	close(std_io[1]);
}
