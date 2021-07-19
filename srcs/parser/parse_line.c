#include "parser.h"

void	dollar_proc(char **line, int *i, char **env, int status)
{
	int		len;
	int		start;
	char	*name;
	char	*value;

	len = 1;
	start = *i;
	while (!ft_strchr(" \t\\\'\"/$", (*line)[++(*i)]))
		len++;
	if (len == 1)
		return ;
	name = ft_substr(*line, start + 1, len - 1);
	if (!name)
		exit(msh_strerror(EXIT_FAILURE));
	value = replace_var(name, env, status);
	*i = *i - ft_strlen(name) + ft_strlen(value) - 1;
	free(name);
	*line = str_replace(*line, start, len, value);
	free(value);
}

void	bslash_proc(char **line, int *i)
{
	*line = str_replace(*line, *i, 1, "");
	(*i)++;
}

void	quotes_dbl(char **line, int *i, char **env, int status)
{
	*line = str_replace(*line, *i, 1, "");
	while ((*line)[*i] && (*line)[*i] != '\"')
	{
		if ((*line)[*i] == '\\' && (*line)[*i + 1] == '$')
			bslash_proc(line, i);
		else if ((*line)[*i] == '$')
			dollar_proc(line, i, env, status);
		else
			(*i)++;
	}
	*line = str_replace(*line, *i, 1, "");
}

void	quotes_one(char **line, int *i)
{
	*line = str_replace(*line, *i, 1, "");
	while ((*line)[*i] && (*line)[*i] != '\'')
		(*i)++;
	*line = str_replace(*line, *i, 1, "");
}

char	*parce_line(char *line, char **env, int status)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			quotes_one(&line, &i);
		else if (line[i] == '\"')
			quotes_dbl(&line, &i, env, status);
		else if (line[i] == '\\')
			bslash_proc(&line, &i);
		else if (line[i] == '$')
			dollar_proc(&line, &i, env, status);
		else
			i++;
	}
	return (line);
}
