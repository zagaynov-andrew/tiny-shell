/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/30 16:50:23 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	msh_set_input(char *in_file, int tmp[], int fd[], int flag_no_input)
{
	if (ft_strcmp(in_file, ""))
		fd[0] = open(in_file, O_RDONLY);
	else if (tmp)
		fd[0] = dup(tmp[0]);
}

static void	msh_set_output(char **path, int tmp[], int fd[])
{
	if (ft_strcmp(path[1], ""))
		fd[1] = open(path[1], O_TRUNC | O_CREAT | O_RDWR);
	else if (ft_strcmp(path[2], ""))
		fd[1] = open(path[2], O_CREAT | O_RDWR);
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
	char	**args;

	// if (!ft_strcmp(((char**)lst->content)[0], "hello"))
	// 	hello();
	// else
	// if (i)
		// ft_putchar_fd(4, 1);
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
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	if (pid < 0)
		printf("Forking error\n");
	return (status);
}

void	msh_simple_cmd_loop(t_list *redirs,
								int tmp[], int fd[], t_list *cmds)
{
	int	num_simple_cmds;
	int	i;
	int flag_no_input;

	num_simple_cmds = ft_lstsize(cmds);
	i = 0;
	flag_no_input = 0;
	while (i < num_simple_cmds)
	{
		if (i)
			msh_set_input(((char **)redirs->content)[0], NULL, fd, flag_no_input);

		flag_no_input = 0;
		dup2(fd[0], 0);
		close(fd[0]);

		if (ft_strcmp(((char **)redirs->content)[1], "") || ft_strcmp(((char **)redirs->content)[2], "") || i == num_simple_cmds - 1)
		{
			msh_set_output(((char **)redirs->content), tmp, fd);
			if (ft_strcmp(((char **)redirs->content)[1], "") || ft_strcmp(((char **)redirs->content)[2], ""))
				flag_no_input = 1;
		}
		else
			msh_create_pipe(fd);
		dup2(fd[1], 1);
		close(fd[1]);

		msh_launch(cmds);


		if (flag_no_input)
		{
			msh_create_pipe(fd);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		cmds = cmds->next;
		redirs = redirs->next;
		i++;
	}
	perror("DONE");
}
