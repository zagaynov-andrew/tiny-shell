#include "parser.h"

static void	lst_add_node(t_list **list, char **data)
{
	t_list	*new;

	new = ft_lstnew((void *)data);
	if (!new)
		exit(msh_strerror(EXIT_FAILURE));
	ft_lstadd_back(list, new);
}

void	checking_redir(char ***split, char	***data_redir, char	***data_arg)
{
	if (is_redir(**split))
	{
		str_array_add_back(data_redir, **split);
		if (!*data_redir)
			exit(msh_strerror(EXIT_FAILURE));
		str_array_add_back(data_redir, *(*split + 1));
		if (!*data_redir)
			exit(msh_strerror(EXIT_FAILURE));
		(*split)++;
	}
	else
	{
		str_array_add_back(data_arg, **split);
		if (!*data_arg)
			exit(msh_strerror(EXIT_FAILURE));
	}
}

static int	empty_cmd(t_list **list, char **split)
{
	if (!split)
	{
		lst_add_node(list, NULL);
		lst_add_node(list, NULL);
		return (1);
	}
	return (0);
}

void	make_cmd_table(t_list **list, char **split)
{
	char	**data_redir;
	char	**data_arg;

	if (empty_cmd(list, split))
		return ;
	while (*split)
	{
		data_arg = NULL;
		data_redir = NULL;
		while (*split && ft_strcmp(*split, "|") != 0)
		{
			checking_redir(&split, &data_redir, &data_arg);
			split++;
		}
		lst_add_node(list, data_arg);
		lst_add_node(list, data_redir);
		data_arg = NULL;
		if (!(*split))
			return ;
		str_array_add_back(&data_arg, *split);
		if (!data_arg)
			exit(msh_strerror(EXIT_FAILURE));
		lst_add_node(list, data_arg);
		split++;
	}
}

t_list	*cmd_table(char **split)
{
	t_list	*lst;

	lst = NULL;
	make_cmd_table(&lst, split);
	return (lst);
}
