/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:55:31 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/06 22:47:37 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	msh_exec(t_list *cmds, t_list *redirs, char **env)
{
	msh_simple_cmd_loop(redirs, cmds, env);
	// dup2(tmp[0], 0);
	// dup2(tmp[1], 1);
	system("chmod 700 file"); //
	return (0);
}
