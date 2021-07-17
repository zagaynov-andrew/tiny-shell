/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:17:15 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/16 18:39:40 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../libs/libft/libft.h"
# include "../test/test_minishell.h"
# include "../builtin/builtin.h"
# include "../minishell.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	msh_exec(t_list *cmds, t_list *redirs, char **env[]);
void	msh_simple_cmd_loop(t_list *redirs, t_list *cmds,
			int standard_io[], char **env[]);
int		processing_redirs(t_list *shell_lst, t_list *redirs);

#endif
