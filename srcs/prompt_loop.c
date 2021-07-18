/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 16:31:36 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 17:31:06 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ctrl_d(char *input)
{
	if (!input)
	{
		ft_putstr_fd("\b\bexit\n", 1);
		return (1);
	}
	return (0);
}

static int	empty_input(char *input)
{
	if (ft_strcmp(input, "") == 0)
	{
		free(input);
		rl_on_new_line();
		rl_redisplay();
		return (1);
	}
	return (0);
}

static void	clear_shell_lst(t_list **shell_lst, t_list **cmds, t_list **redirs)
{
	if (*cmds)
		ft_lstclear(cmds, void_array_free);
	if (*redirs)
		ft_lstclear(redirs, void_array_free);
	if (*shell_lst)
		ft_lstclear(shell_lst, void_array_free);
}

static int	aborted_heredoc(t_list	**shell_lst,
			t_list	**cmds, t_list **redirs, char *input)
{
	if (g_last_exit_status)
	{
		clear_shell_lst(shell_lst, cmds, redirs);
		free(input);
		return (1);
	}
	return (0);
}

void	prompt_loop(t_list	*cmds, t_list *redirs, char **env_copy[])
{
	t_list	*shell_lst;
	char	*input;

	while (1)
	{
		init_signals(sig_catcher_msh);
		input = readline("\033[1;35mminishell $ \033[0m");
		if (ctrl_d(input))
			break ;
		if (empty_input(input))
			continue ;
		if (input)
			add_history(input);
		shell_lst = lexer(input, g_last_exit_status, *env_copy);
		g_last_exit_status = 0;
		if (!shell_lst)
			continue ;
		split_shell_lst(shell_lst, &cmds, &redirs);
		pre_execution(shell_lst, redirs);
		if (aborted_heredoc(&shell_lst, &cmds, &redirs, input))
			continue ;
		msh_exec(cmds, redirs, env_copy);
		clear_shell_lst(&shell_lst, &cmds, &redirs);
		free(input);
	}
}