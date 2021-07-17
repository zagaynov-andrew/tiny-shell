/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/17 19:06:33 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_array_free(void *void_array)
{
	int		i;
	char	**tmp;

	if (!void_array)
		return ;
	i = 0;
	tmp = (char **)void_array;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(void_array);
}

// int	add_redir_input(t_vec *redir, char *redir_str)
// {
// 	char	**redir_arr;

// 	redir_arr = (char **)redir->data;
// 	free(redir_arr[IN_FILE]);
// 	redir_arr[IN_FILE] = ft_strdup(redir_str); // check malloc
// 	if (!redir_arr[IN_FILE])
// 		return (1);
// 	return (0);
// }

int	add_redir(t_vec *redir, char *redir_str, int add_pos, int replace_pos)
{
	char	**redir_arr;

	redir_arr = (char **)redir->data;
	if (ft_strcmp(redir_arr[replace_pos], "") != 0)
	{
		free(redir_arr[replace_pos]);
		redir_arr[replace_pos] = ft_strdup(""); // check malloc
	}
	free(redir_arr[add_pos]);
	redir_arr[add_pos] = ft_strdup(redir_str); // check malloc
	return (0);
}

int	split_shell_lst_element_utils(char *element[], t_vec *cmd, t_vec *redir)
{
	int		j;
	int		ret;

	ret = 0;
	j = 0;
	while (element[j])
	{
		// if (ft_strcmp(element[j], "<") == 0)
		// 	ret = add_redir_input(redir, element[j + 1]); // check return value
		if (ft_strcmp(element[j], "<") == 0)
			ret = add_redir(redir, element[j + 1], IN_FILE, HEREDOC); // check return value
		else if (ft_strcmp(element[j], "<<") == 0)
			ret = add_redir(redir, element[j + 1], HEREDOC, IN_FILE); // check return value
		else if (ft_strcmp(element[j], ">") == 0)
			ret = add_redir(redir, element[j + 1], OUT_FILE, OUT_APP_FILE); // check return value
		else if (ft_strcmp(element[j], ">>") == 0)
			ret = add_redir(redir, element[j + 1], OUT_APP_FILE, OUT_FILE); // check return value
		else
		{
			ft_vec_push(&cmd, ft_strdup(element[j]));
			if (!(cmd->data)[cmd->size - 1])
				return (1);
			j--;
		}
		if (ret)
			return (1);
		j += 2;
	}
	return (0);
}

int	empty_fill_in_redir_lst(t_vec *redir)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!ft_vec_push(&redir, ft_strdup("")))
		{
			ft_vec_free(redir);
			return (1);
		}
		i++;
	}
	ft_vec_push(&redir, NULL);
	return (0);
}

int	split_shell_lst_element(char *element[], t_list **cmd_lst, t_list **redir_lst)
{
	t_vec	*cmd;
	t_vec	*redir;

	cmd = ft_vec_new(2);
	redir = ft_vec_new(5);
	if (!cmd || !redir)
		return (1);
	if (empty_fill_in_redir_lst(redir))
		return (1);
	if (split_shell_lst_element_utils(element, cmd, redir))
		return (1);
	if (!ft_vec_push(&cmd, NULL))
		return (1);
	ft_lstadd_back(cmd_lst, ft_lstnew((char **)(cmd->data)));
	ft_lstadd_back(redir_lst, ft_lstnew((char **)(redir->data)));
	if (!ft_lstlast(*cmd_lst) || !ft_lstlast(*redir_lst))
		return (1);
	free(redir);
	free(cmd);
	return (0);
}

int	split_shell_lst(t_list *shell_lst, t_list **cmds, t_list **redirs)
{
	char	**str_array;

	if (!shell_lst)
		return (1);
	*cmds = NULL;
	*redirs = NULL;
	while (shell_lst)
	{
		str_array = (char **)shell_lst->content;
		if (ft_strcmp(str_array[0], "|") == 0)
		{
			shell_lst = shell_lst->next;
			continue ;
		}
		if (split_shell_lst_element(str_array, cmds, redirs))
			return (1);
		shell_lst = shell_lst->next;
	}
	return (0);
}

t_list	*lexer2(char *line, int status, char **env)
{
	t_list	*shell_lst;
	t_vec	*vec;

	(void)line;
	(void)status;
	(void)env;
	shell_lst = NULL;
	// vec = ft_vec_new(6);
	// ft_vec_push(&vec, (void*)ft_strdup("cat"));
	// ft_vec_push(&vec, (void*)ft_strdup("<<"));
	// ft_vec_push(&vec, (void*)ft_strdup("stop"));
	// // ft_vec_push(&vec, (void*)ft_strdup(">"));
	// // ft_vec_push(&vec, (void*)ft_strdup("file5"));
	// ft_vec_push(&vec, (void*)ft_strdup("<"));
	// ft_vec_push(&vec, (void*)ft_strdup("file"));
	// ft_vec_push(&vec, (void*)ft_strdup("-e"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);

	// vec = ft_vec_new(2);
	// ft_vec_push(&vec, (void*)ft_strdup("|"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);

	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("cat"));
	ft_vec_push(&vec, (void*)ft_strdup("-eb"));
	ft_vec_push(&vec, (void*)ft_strdup(">"));
	ft_vec_push(&vec, (void*)ft_strdup("file"));
	ft_vec_push(&vec, (void*)ft_strdup("<<"));
	ft_vec_push(&vec, (void*)ft_strdup("stop"));
	// ft_vec_push(&vec, (void*)ft_strdup("stop2"));
	// ft_vec_push(&vec, (void*)ft_strdup("<"));
	// ft_vec_push(&vec, (void*)ft_strdup("2"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	free(vec);

	// vec = ft_vec_new(2);
	// ft_vec_push(&vec, (void*)ft_strdup("|"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);

	// vec = ft_vec_new(2);
	// ft_vec_push(&vec, (void*)ft_strdup("cat"));
	// ft_vec_push(&vec, (void*)ft_strdup("-eb"));
	// // ft_vec_push(&vec, (void*)ft_strdup("file3"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);

	// vec = ft_vec_new(2);
	// ft_vec_push(&vec, (void*)ft_strdup("|"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);

	// vec = ft_vec_new(2);
	// ft_vec_push(&vec, (void*)ft_strdup("pwd"));
	// // ft_vec_push(&vec, (void*)ft_strdup("<"));
	// // ft_vec_push(&vec, (void*)ft_strdup("file"));
	// // ft_vec_push(&vec, (void*)ft_strdup(">"));
	// // ft_vec_push(&vec, (void*)ft_strdup("file3"));
	// // ft_vec_push(&vec, (void*)ft_strdup("-b"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	// free(vec);
	return (shell_lst);
}

void	redirs_free(void *redirs)
{
	char	**tmp;

	tmp = (char **)(((t_list *)redirs)->content);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	str_array_free((char ***)(&tmp[4]));
	free(tmp);
}

void	clear_shell_lst(t_list **shell_lst, t_list **cmds, t_list **redirs)
{
	if (*cmds)
		ft_lstclear(cmds, void_array_free);
	if (*redirs)
		ft_lstclear(redirs, void_array_free);
	if (*shell_lst)
		ft_lstclear(shell_lst, void_array_free);
}

int	main(int argc, char *argv[], char *env[])
{
	t_list	*shell_lst;
	t_list	*cmds = NULL;
	t_list	*redirs = NULL;
	char	**env_copy;
	char	*input;

	(void)argc;
	(void)argv;
	cmds = NULL;
	redirs = NULL;
	g_last_exit_status = 0;
	env_copy = str_array_copy((const char **)env);
	if (!env_copy)
		exit(msh_strerror(EXIT_FAILURE));
	while (1)
	{
		init_signals(sig_catcher_msh);
		input = readline("\033[1;35mminishell $ \033[0m");
		if (!input)
		{
			ft_putstr_fd("\b\bexit\n", 1);
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			str_array_free(&env_copy);
			rl_on_new_line();
			rl_redisplay();
			continue ;
		}
		if (input)
			add_history(input);


		shell_lst = lexer2(input, g_last_exit_status, env_copy);
		g_last_exit_status = 0;
		// print_list_str_array(shell_lst);
		if (!shell_lst)
			continue ;

		split_shell_lst(shell_lst, &cmds, &redirs); // check return value

		processing_redirs(shell_lst, redirs); // check return value
		if (g_last_exit_status)
		{
			clear_shell_lst(&shell_lst, &cmds, &redirs);
			free(input);
			continue ;
		}

		msh_exec(cmds, redirs, &env_copy);
		clear_shell_lst(&shell_lst, &cmds, &redirs);
		if (errno != 0)		//
			perror("DONE");	//
		free(input);
	}
	str_array_free(&env_copy);
	return (0);
}

// int	main(int argc, char *argv[], char *env[])
// {
// 	// t_list	*shell_lst = NULL;
// 	// char	**env_copy = NULL;

// 	// env_copy = str_array_copy((const char **)env);
// 	// shell_lst = lexer("echo jhvbk", 0, env_copy);
// 	// ft_lstclear(&shell_lst, void_array_free);
// 	// str_array_free(&env_copy);
// 	char	**array = NULL;
// 	str_array_add_back(&array, "1");
// 	str_array_add_back(&array, "2");
// 	str_array_add_back(&array, "3");
// 	str_array_erase(&array, 2);
// 	print_str_array(array);
// 	str_array_free(&array);
// 	return (1);
// }

// int	main(int argc, char *argv[], char *env[])
// {
// 	char	*heredoc;

// 	heredoc = msh_heredoc("stop");
// 	free(heredoc);
// 	return (1);
// }
