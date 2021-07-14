/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/14 17:54:10 by ngamora          ###   ########.fr       */
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

int	add_redir_input(t_vec *redir, char *redir_str)
{
	char	**redir_arr;

	redir_arr = (char **)redir->data;
	free(redir_arr[0]);
	redir_arr[0] = ft_strdup(redir_str);
	if (!redir_arr[0])
		return (1);
	return (0);
}

int	add_redir(t_vec *redir, char *redir_str, int add_pos, int replse_pos)
{
	char	**redir_arr;

	redir_arr = (char **)redir->data;
	if (ft_strcmp(redir_arr[replse_pos], "") != 0)
	{
		free(redir_arr[replse_pos]);
		redir_arr[replse_pos] = ft_strdup(""); // check malloc
	}
	free(redir_arr[add_pos]);
	redir_arr[add_pos] = ft_strdup(redir_str);
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
		if (ft_strcmp(element[j], "<") == 0)
			ret = add_redir_input(redir, element[j + 1]); // check return value
		else if (ft_strcmp(element[j], "<<") == 0)
			ret = add_redir(redir, element[j + 1], 1, 0); // check return value
		else if (ft_strcmp(element[j], ">") == 0)
			ret = add_redir(redir, element[j + 1], 2, 3); // check return value
		else if (ft_strcmp(element[j], ">>") == 0)
			ret = add_redir(redir, element[j + 1], 3, 2); // check return value
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

t_list	*lexer(char *line, int status, char **env)
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
	// ft_vec_push(&vec, (void*)ft_strdup("1"));
	// ft_vec_push(&vec, (void*)ft_strdup(">"));
	// ft_vec_push(&vec, (void*)ft_strdup("file3"));
	// ft_vec_push(&vec, (void*)ft_strdup("-b"));
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

void	clear_shell_lst(t_list **shell_lst, t_list **cmds, t_list **redirs)
{
	ft_lstclear(cmds, void_array_free);
	ft_lstclear(redirs, void_array_free);
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
	while (1)
	{
		init_signals(sig_catcher_msh);
		input = readline("\033[1;35mminishell $ \033[0m");
		errno = 0;
		if (!input)
		{
			ft_putstr_fd("\b\bexit\n", 1);
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			rl_on_new_line();
			rl_redisplay();
			continue ;
		}
		if (input)
			add_history(input);

		env_copy = str_array_copy((const char **)env);
		if (!env_copy)
			return (msh_strerror(EXIT_FAILURE));
		shell_lst = lexer(input, 0, env_copy);
		if (!shell_lst)
			continue ;
		// print_list_str_array(shell_lst);
		split_shell_lst(shell_lst, &cmds, &redirs); // check return value

		msh_file_creation(shell_lst); // check return value

		msh_exec(cmds, redirs, &env_copy);
		// printf("%d\n", g_last_exit_status);
		clear_shell_lst(&shell_lst, &cmds, &redirs);
		if (errno != 0)		//
			perror("DONE");	//
		free(input);
	}
	str_array_free(env_copy);
	return (0);
}
