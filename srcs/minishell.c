/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/11 19:40:11 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "test/test_minishell.h"
#include "../libft/libft.h"
#include <signal.h>

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

int	split_lst_cmds_redirs(t_list *shell_lst, t_list **cmds, t_list **redirs)
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

// int	main(int argc, char *argv[], char *env[])
// {
// 	// msh_loop(env);
// 	t_list *cmds = NULL;
// 	t_vec	*vec;

// 	vec = ft_vec_new(2);
// 	ft_vec_push(&vec, (void*)ft_strdup("cd"));
// 	// ft_vec_push(&vec, (void*)ft_strdup("-n"));
// 	// ft_vec_push(&vec, (void*)ft_strdup("hello"));
// 	// ft_vec_push(&vec, (void*)ft_strdup("world"));
// 	ft_vec_push(&vec, NULL);
// 	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
// 	free(vec);

// 	// vec = ft_vec_new(4);
// 	// ft_vec_push(&vec, (void*)ft_strdup("head"));
// 	// ft_vec_push(&vec, (void*)ft_strdup("-n"));
// 	// ft_vec_push(&vec, (void*)ft_strdup("3"));
// 	// ft_vec_push(&vec, NULL);
// 	// ft_lstadd_back(&cmds, ft_lstnew(vec->data));
// 	// free(vec);

// 	vec = ft_vec_new(3);
// 	ft_vec_push(&vec, (void*)ft_strdup("grep"));
// 	ft_vec_push(&vec, (void*)ft_strdup("PWD"));
// 	ft_vec_push(&vec, NULL);
// 	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
// 	free(vec);

// 	print_list_str_array(cmds);

// 	t_list *redirs = NULL;

// 	vec = ft_vec_new(4);
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, NULL);
// 	ft_lstadd_back(&redirs, ft_lstnew(vec->data));
// 	free(vec);

// 	vec = ft_vec_new(4);
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, (void*)ft_strdup(""));
// 	ft_vec_push(&vec, NULL);
// 	ft_lstadd_back(&redirs, ft_lstnew(vec->data));
// 	free(vec);

// 	// vec = ft_vec_new(4);
// 	// ft_vec_push(&vec, (void*)ft_strdup("/Users/ngamora/minishell/file2"));
// 	// ft_vec_push(&vec, (void*)ft_strdup(""));
// 	// ft_vec_push(&vec, (void*)ft_strdup(""));
// 	// ft_vec_push(&vec, NULL);
// 	// ft_lstadd_back(&redirs, ft_lstnew(vec->data));
// 	// free(vec);

// 	print_list_str_array(redirs);
// 	msh_file_creation(redirs);
// 	msh_exec(cmds, redirs, env);


// 	ft_lstclear(&cmds, void_array_free);
// 	ft_lstclear(&redirs, void_array_free);
// 	return (0);
// }

int	main(int argc, char *argv[], char *env[])
{
	// msh_loop(env);
	t_list *shell_lst = NULL;
	t_vec	*vec;

	vec = ft_vec_new(6);
	ft_vec_push(&vec, (void*)ft_strdup("cat"));
	ft_vec_push(&vec, (void*)ft_strdup("<<"));
	ft_vec_push(&vec, (void*)ft_strdup("stop"));
	ft_vec_push(&vec, (void*)ft_strdup(">"));
	ft_vec_push(&vec, (void*)ft_strdup("file5"));
	ft_vec_push(&vec, (void*)ft_strdup("<"));
	ft_vec_push(&vec, (void*)ft_strdup("file"));
	ft_vec_push(&vec, (void*)ft_strdup("-eb"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	free(vec);

	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("|"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	free(vec);

	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("cat"));
	ft_vec_push(&vec, (void*)ft_strdup(">"));
	ft_vec_push(&vec, (void*)ft_strdup("file2"));
	ft_vec_push(&vec, (void*)ft_strdup(">>"));
	ft_vec_push(&vec, (void*)ft_strdup("file3"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	free(vec);

	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("pwd"));
	ft_vec_push(&vec, (void*)ft_strdup(">"));
	ft_vec_push(&vec, (void*)ft_strdup("file3"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&shell_lst, ft_lstnew(vec->data));
	free(vec);

	print_list_str_array(shell_lst);

	t_list	*cmds = NULL;
	t_list	*redirs = NULL;
	split_lst_cmds_redirs(shell_lst, &cmds, &redirs);

	print_list_str_array(cmds);
	print_list_str_array(redirs);

	msh_file_creation(shell_lst); // check return value
	msh_exec(cmds, redirs, env);

	ft_lstclear(&cmds, void_array_free);
	ft_lstclear(&redirs, void_array_free);
	ft_lstclear(&shell_lst, void_array_free);
	return (0);
}

