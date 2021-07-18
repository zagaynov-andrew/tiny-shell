/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_lst_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 15:58:45 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 16:45:32 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir(char **redir, char *redir_str,
			int add_pos, int replace_pos)
{
	if (ft_strcmp(redir[replace_pos], "") != 0)
	{
		free(redir[replace_pos]);
		redir[replace_pos] = ft_strdup("");
		if (!redir[replace_pos])
			exit(msh_strerror(EXIT_FAILURE));
	}
	free(redir[add_pos]);
	redir[add_pos] = ft_strdup(redir_str);
	if (!redir[add_pos])
		exit(msh_strerror(EXIT_FAILURE));
}

static void	fill_redir_utils(char *element[], char **redir)
{
	int		j;

	j = 0;
	if (!element)
		return ;
	while (element[j])
	{
		if (ft_strcmp(element[j], "<") == 0)
			add_redir(redir, element[j + 1], IN_FILE, HEREDOC);
		else if (ft_strcmp(element[j], "<<") == 0)
			add_redir(redir, element[j + 1], HEREDOC, IN_FILE);
		else if (ft_strcmp(element[j], ">") == 0)
			add_redir(redir, element[j + 1], OUT_FILE, OUT_APP_FILE);
		else if (ft_strcmp(element[j], ">>") == 0)
			add_redir(redir, element[j + 1], OUT_APP_FILE, OUT_FILE);
		j += 2;
	}
}

static void	empty_fill_in_redir_lst(char **redir[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		*redir = str_array_add_back(redir, "");
		if (!*redir)
			exit(msh_strerror(EXIT_FAILURE));
		i++;
	}
}

void	fill_cmd(char *element[], t_list **cmd_lst)
{
	char	**copy;

	copy = str_array_copy((const char **)element);
	if (!copy)
		exit(msh_strerror(EXIT_FAILURE));
	ft_lstadd_back(cmd_lst, ft_lstnew((void *)copy));
	if (!ft_lstlast(*cmd_lst))
		exit(msh_strerror(EXIT_FAILURE));
}

void	fill_redir(char *element[], t_list **redir_lst)
{
	char	**redir;

	redir = NULL;
	empty_fill_in_redir_lst(&redir);
	fill_redir_utils(element, redir);
	ft_lstadd_back(redir_lst, ft_lstnew((void *)redir));
	if (!ft_lstlast(*redir_lst))
		exit(msh_strerror(EXIT_FAILURE));
}
