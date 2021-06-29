/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:17:15 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/29 16:18:24 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include <sys/wait.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		msh_exec(char *in_file, char *out_file, t_list *lst);
void	msh_set_input(char *in_file, int tmp[], int fd[]);
void	msh_simple_cmd_loop(char *out_file,
								int tmp[], int fd[], t_list *lst);
