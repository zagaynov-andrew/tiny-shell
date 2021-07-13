/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/12 21:40:06 by ngamora          ###   ########.fr       */
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
	if (ft_strcmp(path[2], ""))
		fd[1] = open(path[2], O_TRUNC | O_RDWR);
	else if (ft_strcmp(path[3], ""))
		fd[1] = open(path[3], O_APPEND | O_RDWR);
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
	int	*tmp;

	if (!(tmp = (int *)malloc(sizeof(int))))
		return (NULL);
	*tmp = num;
	return (tmp);
}

static int		len_str_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}

static int	msh_launch_builtin(t_list *cmd, char **env[])
{
	char	**args;

	args = (char **)cmd->content;
	if (!ft_strcmp(args[0], "echo"))
		return (msh_echo(len_str_array(args), args, *env));
	else if (!ft_strcmp(args[0], "pwd"))
		return(msh_pwd(len_str_array(args), args, *env));
	else if (!ft_strcmp(args[0], "cd"))
		return(msh_cd(len_str_array(args), (const char **)args, env));
	else if (!ft_strcmp(args[0], "env"))
		return(msh_env(len_str_array(args), args, *env));
	else if (!ft_strcmp(args[0], "export"))
		return(msh_export(len_str_array(args), (const char **)args, env));
	else if (!ft_strcmp(args[0], "unset"))
		return(msh_unset(len_str_array(args), (const char **)args, env));
	return (-1);
}

static int	msh_launch(t_list *cmd, t_list **pid_lst, char **env[])
{
	int		pid;
	int		status;
	char	**args;

	status = msh_launch_builtin(cmd, env);
	if (status != -1)
		return (status);
	args = (char **)cmd->content;
	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		perror("ERROR1");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
		ft_lstadd_back(pid_lst, ft_lstnew((void *)ft_int_dup(pid))); // Check malloc
	if (pid < 0)
		perror("Forking error\n"); //
	return (-1);
}

int	cmd_waiting(t_list	**pid_lst)
{
	int		pid;
	int		status;
	t_list	*pid_lst_copy;

	pid_lst_copy = *pid_lst;
	while (*pid_lst)
	{
		pid = *((int *)((*pid_lst)->content));
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		(*pid_lst) = (*pid_lst)->next;
	}
	ft_lstclear(&pid_lst_copy, free);
	return (status); // incorrect exit status
}

static void	inc_lst(t_list **cmds, t_list **redirs)
{
	*redirs = (*redirs)->next;
	*cmds = (*cmds)->next;
}

int	msh_simple_cmd_loop(t_list *cmds, t_list *redirs, int standard_io[], char **env[])
{
	int		num_cmds;
	int		i;
	int		fd[2];
	t_list	*pid_lst;
	int		status[2];

	msh_set_input(((char **)redirs->content)[0], standard_io, fd);
	num_cmds = ft_lstsize(cmds);
	pid_lst = NULL;
	i = -1;
	while (++i < num_cmds)
	{
		if (i != num_cmds - 1)
			msh_create_pipe(fd);
		msh_set_output(((char **)redirs->content), standard_io, fd, i == num_cmds - 1);
		status[0] = msh_launch(cmds, &pid_lst, env);
		if (i != num_cmds - 1)
			status[0] = -1;
		redirs = redirs->next;
		if (i != num_cmds - 1)
			msh_set_input(((char **)redirs->content)[0], NULL, fd);
		cmds = cmds->next;
	}
	if (errno != 0)		//
		perror("DONE");	//
	status[1] = cmd_waiting(&pid_lst);
	if (status[0] != -1)
		return (status[0]);
	return (status[1]);
}
