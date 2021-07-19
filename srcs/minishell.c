/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/19 16:31:12 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_list	*cmds;
	t_list	*redirs;
	char	**env_copy;
	t_list	*shell_lst;

	(void)argc;
	(void)argv;
	cmds = NULL;
	redirs = NULL;
	env_copy = str_array_copy((const char **)env);
	if (!env_copy)
		exit(msh_strerror(EXIT_FAILURE));
	prompt_loop(&cmds, &redirs, &env_copy, &shell_lst);
	clear_shell_lst(&shell_lst, &cmds, &redirs, NULL);
	str_array_free(&env_copy);
	return (g_last_exit_status);
}
