/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 15:04:41 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/19 19:07:10 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_catcher_msh(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\033[1;35mminishell $ \033[0m", 1);
		ft_putstr_fd(rl_line_buffer, 1);
		ft_putstr_fd("  \b\b", 1);
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\033[1;35mminishell $ \033[0m", 1);
		ft_putstr_fd(rl_line_buffer, 1);
		ft_putstr_fd("  \b\b\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_catcher_heredoc(int sig)
{
	int	fd_pipe[2];

	if (sig == SIGQUIT)
	{
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(rl_line_buffer, 1);
		ft_putstr_fd("  \b\b", 1);
		init_signals(sig_catcher_msh);
	}
	else if (sig == SIGINT)
	{
		pipe(fd_pipe);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(rl_line_buffer, 1);
		ft_putstr_fd("  \b\b", 1);
		if (!ft_strcmp(rl_line_buffer, ""))
			ft_putstr_fd("\n", 1);
		errno = 0;
		g_last_exit_status = 1;
		init_signals(sig_catcher_msh);
	}
}

void	sig_catcher_cmds(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_last_exit_status = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_last_exit_status = 130;
	}
}

void	init_signals(void (*sig_catcher)(int))
{
	if (signal(SIGINT, sig_catcher) == SIG_ERR)
		exit(msh_strerror(EXIT_FAILURE));
	if (signal(SIGQUIT, sig_catcher) == SIG_ERR)
		exit(msh_strerror(EXIT_FAILURE));
}
