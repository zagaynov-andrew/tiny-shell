/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:17:15 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/17 20:36:30 by ngamora          ###   ########.fr       */
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
int		pre_execution(t_list *shell_lst, t_list *redirs);
int		msh_launch(t_list *cmd, t_list **pid_lst, char **env[]);
void	set_input(char **redirs, int tmp[], int fd[]);
void	set_output(char **redirs, int tmp[], int fd[], int flag_last);
void	msh_create_pipe(int fd[]);
void	processint_pids(t_list **pid_lst, int status[]);

#endif
