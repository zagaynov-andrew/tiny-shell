#include "parser.h"

int	is_built_in(char *str)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = ft_tolower_line(ft_strdup(str));
	if (ft_strcmp(tmp, "echo") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "cd") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "pwd") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "export") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "unset") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "env") == 0)
		ret = 1;
	else if (ft_strcmp(tmp, "exit") == 0)
		ret = 1;
	free(tmp);
	return (ret);
}

char	*remove_q(char *str)
{
	int	i;

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

void	remove_quotes_fl(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!is_redir(arr[i]))
			arr[i] = remove_q(arr[i]);
		i++;
	}
}
