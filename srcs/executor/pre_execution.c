/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:04:19 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/17 20:36:22 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	create_files(char **cmd_array)
{
	int		fd;
	int		i;

	i = 0;
	while (cmd_array[i])
	{
		if (ft_strcmp(cmd_array[i], ">") == 0)
		{
			fd = open(cmd_array[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
			close(fd);
			if (fd < 0)
				return (1);
			i++;
		}
		else if (ft_strcmp(cmd_array[i], ">>") == 0)
		{
			fd = open(cmd_array[i + 1], O_CREAT | O_RDWR, 0644);
			close(fd);
			if (fd < 0)
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

static int	launch_heredocs_utils(char **cmd_array,
				char **redir_array, char **heredoc, int i)
{
	int	std_in;

	std_in = dup(0);
	*heredoc = msh_heredoc(cmd_array[i + 1]);
	if (g_last_exit_status)
	{
		dup2(std_in, 0);
		return (1);
	}
	free(redir_array[HEREDOC]);
	redir_array[HEREDOC] = *heredoc;
	return (0);
}

static void	launch_heredocs(char **cmd_array, char **redir_array)
{
	int		fd;
	int		i;
	char	*heredoc;

	heredoc = NULL;
	i = 0;
	while (cmd_array[i])
	{
		if (ft_strcmp(cmd_array[i], "<") == 0)
		{
			free(redir_array[HEREDOC]);
			redir_array[HEREDOC] = ft_strdup("");
			if (!redir_array[HEREDOC])
				exit(msh_strerror(EXIT_FAILURE));
			i += 2;
			continue ;
		}
		if (ft_strcmp(cmd_array[i], "<<") == 0)
		{
			launch_heredocs_utils(cmd_array, redir_array, &heredoc, i);
			i++;
		}
		i++;
	}
}

int	pre_execution(t_list *shell_lst, t_list *redirs)
{
	char	**shell_data;
	char	**redir_data;

	while (shell_lst)
	{
		shell_data = (char **)(shell_lst->content);
		redir_data = (char **)(redirs->content);
		launch_heredocs(shell_data, redir_data);
		if (g_last_exit_status)
			return (1);
		if (create_files(shell_data))
			return (1);
		shell_lst = shell_lst->next;
		redirs = redirs->next;
	}
	return (0);
}
