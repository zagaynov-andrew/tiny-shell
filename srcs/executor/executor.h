/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:17:15 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/30 15:16:55 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../../libft/libft.h"
#include "../test/test_minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		msh_exec(t_list *cmds, t_list *redirs);
void	msh_set_input(char *in_file, int tmp[], int fd[], int flag_no_input);
void	msh_simple_cmd_loop(t_list *redirs,
								int tmp[], int fd[], t_list *cmds);
void	str_array_free(void *str_array);
void	msh_file_creation(t_list *redirs);

#endif
