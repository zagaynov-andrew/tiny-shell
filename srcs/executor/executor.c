/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:55:31 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/03 20:14:13 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	msh_exec(t_list *cmds, t_list *redirs)
{
	int	tmp[2];
	int	fd[2];

	tmp[0] = dup(0);
	tmp[1] = dup(1);
	msh_set_input(((char **)redirs->content)[0], tmp, fd);
	msh_simple_cmd_loop(redirs, tmp, fd, cmds);
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	system("chmod 700 file"); //
	return (0);
}
