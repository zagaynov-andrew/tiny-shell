/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_substitution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 20:25:13 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/17 20:25:47 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	set_input(char **redirs, int tmp[], int fd[])
{
	int	fd_pipe[2];

	if (ft_strcmp(redirs[IN_FILE], "") != 0)
		fd[0] = open(redirs[IN_FILE], O_RDONLY);
	else if (!redirs[HEREDOC] || ft_strcmp(redirs[HEREDOC], "") != 0)
	{
		pipe(fd_pipe);
		fd[1] = fd_pipe[1];
		fd[0] = fd_pipe[0];
		dup2(fd[0], 0);
		close(fd[0]);
		if (redirs[HEREDOC])
			write(fd[1], redirs[HEREDOC], ft_strlen(redirs[HEREDOC]));
		close(fd[1]);
		return ;
	}
	else if (tmp)
		fd[0] = dup(tmp[0]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	set_output(char **redirs, int tmp[], int fd[], int flag_last)
{
	int	fd_pipe[2];

	if (ft_strcmp(redirs[OUT_FILE], ""))
		fd[1] = open(redirs[OUT_FILE], O_TRUNC | O_RDWR);
	else if (ft_strcmp(redirs[OUT_APP_FILE], ""))
		fd[1] = open(redirs[OUT_APP_FILE], O_APPEND | O_RDWR);
	else if (flag_last)
	{
		fd[1] = dup(tmp[1]);
		dup2(fd[1], 1);
		return ;
	}
	else
		return ;
	dup2(fd[1], 1);
	close(fd[1]);
}

void	msh_create_pipe(int fd[])
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	fd[1] = fd_pipe[1];
	fd[0] = fd_pipe[0];
	dup2(fd[1], 1);
	close(fd[1]);
}
