#include "parser.h"

int		is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

char	*remove_q(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			str = str_replace(str, i, 1, "");
			i--;
		}
			i++;
	}
	return (str);
}

void	evaluate_replace_arg(char **arr, char **env, int status)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (i == 0 && !is_built_in(arr[i]))
			check_cmd(arr[i], env);
		arr[i] = parce_line(arr[i], env, status);
		i++;
	}
}

void	remove_quotes_fl(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (!is_redir(arr[i]))
			arr[i] = remove_q(arr[i]);
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
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		if ((char **)(tmp->content))
			replace_var_cmd((char **)(tmp->content), env, status);
		tmp = tmp->next;
	}
}


// void	change_var(char **split, char **env, int status)
// {
// 	int i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		if (i == 0)
// 		{
// 			split[i] = check_cmd(split[i], env);
// 			split[i] = parce_line(split[i], env, status);
// 		}
// 		else if (ft_strncmp("<<", split[i - 1], 2))
// 			split[i] = parce_line(split[i], env, status);
// 		i++;
// 	}
// }

t_list	*lexer(char *line, int status, char **env)
{
	t_list	*node;
	char	**split;

	if (status != 0)
		return (NULL);
	(void)env;
	node = NULL;
	split = ft_split_cmd_args(line);
	print_str_array(split);
	ft_putstr_fd("\n\n", 1);
	// change_var(split, env, status);
	node = cmd_table(split);
	change_var_cmd(&node, env, status);
	str_array_free(&split);
	// free_split(split);
	return (node);
}
