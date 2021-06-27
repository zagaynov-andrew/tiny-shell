/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/27 19:12:35 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_list	*parse_cmd(char *cmd)
{
	t_list	*args;

	args = NULL;
	ft_lstadd_back(&args, ft_lstnew((void*)ft_strdup("ls")));
	return (args);
}

int		msh_launch(char *args[], char *env[])
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if ((pid = fork()) == 0)
	{
		if (execve(args[0], args, env) == -1)
			printf("EXIT_FAILURE\n");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (pid < 0)
	{
		// Ошибка при форкинге
	}
	return (0);
}

void	msh_loop(char *env[])
{
	t_list	*lst;
	char	**args;
	int		status;
	int		i;

	status = 0;
	while (!status)
	{
		lst = parse_cmd("command");
		args = ft_lst_to_array(lst);

		// status = msh_exec(args, env);
		ft_lstclear(&lst, free);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	// msh_loop(env);

	t_list *lst;
	char **arr_1;
	arr_1 = (char**)ft_calloc(2, sizeof(char*));
	for (int i = 0; i < 2; i++)
		arr_1[i] = (char*)ft_calloc(10, sizeof(char));
	arr_1[0] = "ls";
	arr_1[1] = NULL;
	char **arr_2;
	arr_2 = (char**)ft_calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++)
		arr_2[i] = (char*)ft_calloc(10, sizeof(char));
	arr_2[0] = "grep";
	arr_2[1] = "file";
	arr_2[2] = NULL;
	char **arr_3;
	arr_3 = (char**)ft_calloc(4, sizeof(char*));
	// for (int i = 0; i < 4; i++)
	// 	arr_3[i] = (char*)ft_calloc(10, sizeof(char));
	// arr_3[0] = "cat";
	// arr_3[1] = "-e";
	// arr_3[2] = "-b";
	// arr_3[3] = NULL;
	ft_lstadd_back(&lst, ft_lstnew((void*)arr_1));
	ft_lstadd_back(&lst, ft_lstnew((void*)arr_2));
	// ft_lstadd_back(&lst, ft_lstnew((void*)arr_3));
	msh_exec(NULL, NULL, lst);
	return (0);
}

