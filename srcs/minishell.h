/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:28:17 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/14 15:56:36 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "executor/executor.h"
#include "test/test_minishell.h"
#include "../libs/libft/libft.h"
#include "parser/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

int		g_last_exit_status;

void	void_array_free(void *void_array);
int		add_redir_input(t_vec *redir, char *redir_str);
int		add_redir(t_vec *redir, char *redir_str, int add_pos, int replse_pos);
int		split_shell_lst_element_utils(char *element[], t_vec *cmd, t_vec *redir);
int		empty_fill_in_redir_lst(t_vec *redir);
int		split_shell_lst_element(char *element[], t_list **cmd_lst, t_list **redir_lst);
int		split_lst_cmds_redirs(t_list *shell_lst, t_list **cmds, t_list **redirs);
int		msh_perror(char *str, int ret);
int		msh_strerror(int ret);
void	sig_catcher_msh(int sig);
void	sig_catcher_cmds(int sig);
void	init_signals(void (*sig_catcher)(int));

#endif
