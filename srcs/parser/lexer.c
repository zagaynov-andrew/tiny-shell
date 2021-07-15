#include "parser.h"

void	change_var(char **split, char **env, int status)
{
	int i;

	i = 0;
	while (split[i])
	{
		if (i == 0)
		{
			split[i] = check_cmd(split[i], env);
			split[i] = parce_line(split[i], env, status);
		}
		else if (ft_strncmp("<<", split[i - 1], 2))
			split[i] = parce_line(split[i], env, status);
		i++;
	}
}

t_list	*lexer(char *line, int status, char **env)
{
	t_list	*node;
	char	**split;

	if (status != 0)
		return (NULL);
	// (void)env;
	node = NULL;
	split = ft_split_cmd_args(line);
	change_var(split, env, status);
	node = cmd_table(split);
	free_split(split);
	return (node);
}
