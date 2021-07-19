/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_substitution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 20:25:13 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 15:55:24 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	open_input_file(char *path, int fd[])
{
	int	fd_pipe[2];
	int	new_fd;

	new_fd = open(path, O_RDONLY);
	if (new_fd == -1)
	{
		msh_strerror_arg(1, path);
		pipe(fd_pipe);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return (1);
	}
	else
		fd[0] = new_fd;
	return (0);
}

void	write_to_heredoc(char *heredoc)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	dup2(fd_pipe[0], 0);
	close(fd_pipe[0]);
	if (heredoc)
		write(fd_pipe[1], heredoc, ft_strlen(heredoc));
	close(fd_pipe[1]);
}

int	set_input(char **redirs, int tmp[], int fd[])
{
	if (ft_strcmp(redirs[IN_FILE], "") != 0)
	{
		if (open_input_file(redirs[IN_FILE], fd))
			return (1);
	}
	else if (!redirs[HEREDOC] || ft_strcmp(redirs[HEREDOC], "") != 0)
	{
		write_to_heredoc(redirs[HEREDOC]);
		return (0);
	}
	else if (tmp)
		fd[0] = dup(tmp[0]);
	dup2(fd[0], 0);
	close(fd[0]);
	return (0);
}

void	set_output(char **redirs, int tmp[], int fd[], int flag_last)
{
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
