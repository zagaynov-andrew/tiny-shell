#include "parser.h"

int msh_perror(char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}
int msh_strerror(int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

void	lst_add_node(t_list **list, char **data)
{
	t_list *new;

	new = ft_lstnew((void *)data);
	if (!new)
		exit(msh_strerror(EXIT_FAILURE));
	ft_lstadd_back(list, new);
}

int		is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

void	make_cmd_table(t_list **list, char **split)
{
	char	**data_redir;
	char	**data_arg;

	while (*split)
	{
		data_arg = NULL;
		data_redir = NULL;
		while (*split && ft_strcmp(*split, "|") != 0)
		{
			if (is_redir(*split))
			{
				str_array_add_back(&data_redir, *split);
				str_array_add_back(&data_redir, *(split + 1));
				split++;
			}
			else
				str_array_add_back(&data_arg, *split);
			split++;
		}
		lst_add_node(list, data_arg);
		lst_add_node(list, data_redir);
		data_arg = NULL;
		if (!(*split))
			return ;
		str_array_add_back(&data_arg, *split);
		lst_add_node(list, data_arg);
		split++;
	}
}

t_list *cmd_table(char **split)
{
	t_list *lst;

	lst = NULL;
	make_cmd_table(&lst, split);
	return (lst);
}