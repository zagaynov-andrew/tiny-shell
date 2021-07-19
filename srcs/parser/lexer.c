#include "parser.h"

void	evaluate_replace_arg(char **arr, char **env, int status)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (i == 0 && !is_built_in(arr[i]))
		{
			arr[i] = parce_line(arr[i], env, status);
			arr[i] = check_cmd(arr[i], env);
		}
		else
			arr[i] = parce_line(arr[i], env, status);
		i++;
	}
}

void	replace_var_cmd(char **arr, char **env, int status)
{
	if (!is_redir(*arr) && ft_strcmp(*arr, "|"))
		evaluate_replace_arg(arr, env, status);
	else
		remove_quotes_fl(arr);
}

void	change_var_cmd(t_list **list, char **env, int status)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((char **)(tmp->content))
			replace_var_cmd((char **)(tmp->content), env, status);
		tmp = tmp->next;
	}
}

t_list	*lexer(char *line, int status, char **env)
{
	t_list	*node;
	char	**split;

	node = NULL;
	split = ft_split_cmd_args(line);
	print_str_array(split);
	ft_putstr_fd("\n\n", 1);
	node = cmd_table(split);
	change_var_cmd(&node, env, status);
	str_array_free(&split);
	return (node);
}
