#include "executor.h"

static void	create_files(char **cmd_array)
{
	int		fd;
	int		i;

	i = 0;
	if (!cmd_array)
		return ;
	while (cmd_array[i])
	{
		if (ft_strcmp(cmd_array[i], ">") == 0)
		{
			fd = open(cmd_array[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd != -1)
				close(fd);
			i++;
		}
		else if (ft_strcmp(cmd_array[i], ">>") == 0)
		{
			fd = open(cmd_array[i + 1], O_CREAT | O_RDWR, 0644);
			if (fd != -1)
				close(fd);
			i++;
		}
		i++;
	}
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
	int		i;
	char	*heredoc;

	heredoc = NULL;
	i = -1;
	if (!cmd_array)
		return ;
	while (cmd_array[++i])
	{
		if (ft_strcmp(cmd_array[i], "<") == 0)
		{
			free(redir_array[HEREDOC]);
			redir_array[HEREDOC] = ft_strdup("");
			if (!redir_array[HEREDOC])
				exit(msh_strerror(EXIT_FAILURE));
			i++;
			continue ;
		}
		if (ft_strcmp(cmd_array[i], "<<") == 0)
		{
			launch_heredocs_utils(cmd_array, redir_array, &heredoc, i);
			i++;
		}
	}
}

void	pre_execution(t_list *shell_lst, t_list *redirs)
{
	char	**shell_data;
	char	**redir_data;
	int		i;

	i = 0;
	while (shell_lst)
	{
		if (i % 3 == 0 || i % 3 == 2)
		{
			shell_lst = shell_lst->next;
			i++;
			continue ;
		}
		shell_data = (char **)(shell_lst->content);
		redir_data = (char **)(redirs->content);
		launch_heredocs(shell_data, redir_data);
		create_files(shell_data);
		shell_lst = shell_lst->next;
		redirs = redirs->next;
		i++;
	}
}
