/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/03 20:38:39 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	msh_set_input(char *in_file, int tmp[], int fd[])
{
	if (ft_strcmp(in_file, ""))
		fd[0] = open(in_file, O_RDONLY);
	else if (tmp)
		fd[0] = dup(tmp[0]);
	dup2(fd[0], 0);
	close(fd[0]);
}

static void	msh_set_output(char **path, int tmp[], int fd[], int flag_last)
{
	if (ft_strcmp(path[1], ""))
		fd[1] = open(path[1], O_TRUNC | O_RDWR);
	else if (ft_strcmp(path[2], ""))
		fd[1] = open(path[2], O_APPEND | O_RDWR);
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

static void	msh_create_pipe(int fd[])
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	fd[1] = fd_pipe[1];
	fd[0] = fd_pipe[0];
	dup2(fd[1], 1);
	close(fd[1]);
}

static int	*ft_int_dup(int num)
{
	int *tmp;

	if (!(tmp = (int *)malloc(sizeof(int))))
		return (NULL);
	*tmp = num;
	return (tmp);
}

static t_list	*msh_launch(t_list *lst, t_list *pid_lst)
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
		ft_lstadd_back(&pid_lst, ft_lstnew((void*)ft_int_dup(pid)));
		// waitpid(pid, &status, WUNTRACED);
		// while (!WIFEXITED(status) && !WIFSIGNALED(status))
		// 	waitpid(pid, &status, WUNTRACED);
	}
	if (pid < 0)
		printf("Forking error\n");
	return (pid_lst);
}

void	msh_simple_cmd_loop(t_list *redirs,
								int tmp[], int fd[], t_list *cmds)
{
	int	num_cmds;
	int	i;
	t_list *pid_lst;

	num_cmds = ft_lstsize(cmds);
	pid_lst = NULL;
	i = 0;
	while (i < num_cmds)
	{
		if (i != num_cmds - 1)
			msh_create_pipe(fd);
		msh_set_output(((char **)redirs->content), tmp, fd, i == num_cmds - 1);
		pid_lst = msh_launch(cmds , pid_lst);
		redirs = redirs->next;
		if (i != num_cmds - 1)
			msh_set_input(((char **)redirs->content)[0], NULL, fd);
		cmds = cmds->next;
		i++;
	}
	while (pid_lst)
	{
		int pid = *((int *)(pid_lst->content));
		int status;
		ft_putstr_fd("pid = ", 2);
		ft_putnbr_fd(pid, 2);
		ft_putstr_fd("\n", 2);
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		pid_lst = pid_lst->next;
	}

	perror("DONE");
}
