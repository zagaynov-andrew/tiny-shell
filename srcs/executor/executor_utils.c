/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:20:58 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 14:20:42 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	*ft_int_dup(int num)
{
	int	*tmp;

	tmp = (int *)malloc(sizeof(int));
	if (!tmp)
		exit(msh_strerror(EXIT_FAILURE));
	*tmp = num;
	return (tmp);
}

static int	msh_launch_builtin(t_list *cmd, char **env[])
{
	char	**args;
	int		args_size;

	args = (char **)cmd->content;
	args_size = str_array_size((const char **)args);
	if (ft_strcmp(args[0], "echo") == 0)
		return (msh_echo(args_size, args, *env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (msh_pwd(args_size, args, *env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (msh_cd(args_size, (const char **)args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (msh_env(args_size, args, *env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (msh_export(args_size, (const char **)args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (msh_unset(args_size, (const char **)args, env));
	return (-1);
}

int	msh_launch(t_list *cmd, t_list **pid_lst, char **env[])
{
	int		pid;
	int		status;
	t_list	*new_node;

	status = msh_launch_builtin(cmd, env);
	if (status != -1)
		return (status);
	pid = fork();
	if (pid == 0)
	{
		execvp(((char **)cmd->content)[0], ((char **)cmd->content));
		exit(msh_strerror(127));
	}
	if (pid > 0)
	{
		init_signals(sig_catcher_cmds);
		new_node = ft_lstnew((void *)ft_int_dup(pid));
		if (!new_node || !(new_node->content))
			exit(msh_strerror(EXIT_FAILURE));
		ft_lstadd_back(pid_lst, new_node);
	}
	if (pid < 0)
		exit(msh_perror("Forking error", EXIT_FAILURE));
	return (-1);
}

static int	cmd_waiting(t_list	*pid_lst)
{
	int		pid;
	int		status;

	while (pid_lst)
	{
		pid = *((int *)(pid_lst->content));
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		pid_lst = pid_lst->next;
	}
	if (!pid_lst)
		return (0);
	if (WIFSIGNALED(status))
		return (g_last_exit_status);
	return (WEXITSTATUS(status));
}

void	processint_pids(t_list **pid_lst, int status[])
{
	status[1] = cmd_waiting(*pid_lst);
	ft_lstclear(pid_lst, free);
	if (status[0] != -1)
		g_last_exit_status = status[0];
	else
		g_last_exit_status = status[1];
}
