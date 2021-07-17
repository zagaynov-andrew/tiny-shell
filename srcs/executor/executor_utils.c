/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/17 16:16:43 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	msh_set_input(char **redirs, int tmp[], int fd[])
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
		perror("msh_set_input <<");
		return ;
	}
	else if (tmp)
		fd[0] = dup(tmp[0]);
	dup2(fd[0], 0);
	close(fd[0]);
}

static void	msh_set_output(char **redirs, int tmp[], int fd[], int flag_last)
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

	tmp = (int *)malloc(sizeof(int));
	if (!tmp)
		return (NULL);
	*tmp = num;
	return (tmp);
}

static int	len_str_array(char **str_array)
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
	if (ft_strcmp(args[0], "/bin/echo") == 0)
		return (msh_echo(len_str_array(args), args, *env));
	else if (ft_strcmp(args[0], "/bin/pwd") == 0)
		return (msh_pwd(len_str_array(args), args, *env));
	else if (ft_strcmp(args[0], "/usr/bin/cd") == 0)
		return (msh_cd(len_str_array(args), (const char **)args, env));
	else if (ft_strcmp(args[0], "/usr/bin/env") == 0)
		return (msh_env(len_str_array(args), args, *env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (msh_export(len_str_array(args), (const char **)args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (msh_unset(len_str_array(args), (const char **)args, env));
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
		exit(msh_strerror(127));
	}
	if (pid > 0)
	{
		init_signals(sig_catcher_cmds);
		ft_lstadd_back(pid_lst, ft_lstnew((void *)ft_int_dup(pid))); // Check malloc
	}
	if (pid < 0)
		exit(msh_perror("Forking error", EXIT_FAILURE));
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
	// ft_putstr_fd("WIFEXITED(status) = ", 2);
	// ft_putnbr_fd(WIFEXITED(status), 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("WIFSIGNALED(status) = ", 2);
	// ft_putnbr_fd(WIFSIGNALED(status), 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("WEXITSTATUS(status) = ", 2);
	// ft_putnbr_fd(WEXITSTATUS(status), 2);
	// ft_putstr_fd("\n", 2);


	ft_lstclear(&pid_lst_copy, free);
	if (WIFSIGNALED(status))
		return (g_last_exit_status);
	return (WEXITSTATUS(status));
}

// static void	inc_lst(t_list **cmds, t_list **redirs)
// {
// 	*redirs = (*redirs)->next;
// 	*cmds = (*cmds)->next;
// }

void	msh_simple_cmd_loop(t_list *cmds, t_list *redirs,
			int standard_io[], char **env[])
{
	int		num_cmds;
	int		i;
	int		fd[2];
	t_list	*pid_lst;
	int		status[2];

	msh_set_input((char **)(redirs->content), standard_io, fd);
	num_cmds = ft_lstsize(cmds);
	pid_lst = NULL;
	i = -1;
	while (++i < num_cmds)
	{
		if (i != num_cmds - 1)
			msh_create_pipe(fd);
		perror("msh_simple_cmd_loop 1");
		msh_set_output(((char **)redirs->content),
			standard_io, fd, i == num_cmds - 1);
		perror("msh_simple_cmd_loop 2");
		status[0] = msh_launch(cmds, &pid_lst, env);
		if (i != num_cmds - 1)
			status[0] = -1;
		redirs = redirs->next;
		if (i != num_cmds - 1)
			msh_set_input((char **)(redirs->content), NULL, fd);
		cmds = cmds->next;
	}
	if (errno != 0)		//
		perror("DONE");	//
	status[1] = cmd_waiting(&pid_lst);

	if (status[0] != -1)
		g_last_exit_status = status[0];
	else
		g_last_exit_status = status[1];
}
