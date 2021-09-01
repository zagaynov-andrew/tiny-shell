#include "parser.h"

char	*str_replace(char *line, int start, int len, char *replace)
{
	char	*left;
	char	*right;
	char	*tmp;

	left = ft_substr(line, 0, start);
	right = ft_strdup(line + start + len);
	if (!left && !right)
		exit(msh_strerror(EXIT_FAILURE));
	free(line);
	tmp = left;
	left = ft_strjoin(left, replace);
	free(tmp);
	if (!left)
		exit(msh_strerror(EXIT_FAILURE));
	tmp = left;
	left = ft_strjoin(left, right);
	free(tmp);
	free(right);
	if (!left)
		exit(msh_strerror(EXIT_FAILURE));
	return (left);
}

static void	dollar_proc_utils(int *i, int *len, int start)
{
	*len = 2;
	(*i) = start + 2;
}

void	dollar_proc(char **line, int *i, char **env, int status)
{
	int		len;
	int		start;
	char	*name;
	char	*value;

	len = 1;
	start = *i;
	if (ft_strnstr(*line + (*i), "$?", ft_strlen(*line + (*i))) == *line + (*i))
		dollar_proc_utils(i, &len, start);
	else
	{
		while (!ft_strchr(" \t\\\'\"/$=@#%^:,.-+", (*line)[++(*i)]))
			len++;
		if (len == 1)
			return ;
	}
	name = ft_substr(*line, start + 1, len - 1);
	if (!name)
		exit(msh_strerror(EXIT_FAILURE));
	value = replace_var(name, env, status);
	*i = *i - ft_strlen(name) + ft_strlen(value) - 1;
	free(name);
	*line = str_replace(*line, start, len, value);
	free(value);
}
