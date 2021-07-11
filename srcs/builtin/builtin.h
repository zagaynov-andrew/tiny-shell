/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:07:23 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/11 13:28:05 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../libft/libft.h"
# include "../test/test_minishell.h" //
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	msh_echo(int argc, char *argv[], char *env[]);
int	msh_pwd(int argc, char *argv[], char *env[]);
int	msh_cd(int argc, char *argv[], char *env[]);
int	msh_env(int argc, char *argv[], char *env[]);
int	msh_export(const int argc, const char *argv[], char **env[]);
int	is_valid_env_name(const char *env_ptr);
int	get_env_pos(const char *name, const char **env);

#endif
