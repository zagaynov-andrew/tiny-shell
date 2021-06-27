/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/27 18:24:47 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	msh_set_input(char *in_file, int tmp[], int fd[])
{
	if (in_file)
		fd[0] = open(in_file, O_RDONLY);
	else
		fd[0] = dup(tmp[0]);
}

static void	msh_set_output(char *out_file, int tmp[], int fd[])
{
	if (out_file)
		fd[1] = open(out_file, O_TRUNC | O_CREAT | O_RDWR);
	else
		fd[1] = dup(tmp[1]);
}

static void	msh_create_pipe(int fd[])
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	fd[1] = fd_pipe[1];
	fd[0] = fd_pipe[0];
}

static int	msh_launch(t_list *lst)
{
	int		pid;
	int		status;
	int		wpid;
	char	**args;

	pid = fork();
	if (pid == 0)
	{
		args = (char **)lst->content;
		execvp(args[0], args);
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (pid < 0)
		printf("Forking error\n");
	return (status);
}

void	msh_simple_cmd_loop(char *out_file,
								int tmp[], int fd[], t_list *lst)
{
	int	num_simple_cmds;
	int	pid;
	int	i;

	num_simple_cmds = ft_lstsize(lst);
	i = 0;
	while (i < num_simple_cmds)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		if (i == num_simple_cmds - 1)
			msh_set_output(out_file, tmp, fd);
		else
			msh_create_pipe(fd);
		dup2(fd[1], 1);
		close(fd[1]);
		msh_launch(lst);
		lst = lst->next;
		i++;
	}
}
