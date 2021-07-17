#include "parser.h"

static char *parse_slash(char *line, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = malloc(ft_strlen(line) - 1);
	if (!tmp)
	{
		perror("Error parse_slash malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(tmp, line, ft_strlen(line) - ft_strlen(&line[j]));
	ft_strncpy(&tmp[j], &line[j + 1], ft_strlen(line));
	free(line);
	return (tmp);
}

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

void	dollar_proc(char **line, int *i, char **env, int status)
{
	int		len;
	int		start;
	char 	*name;
	char 	*value;

	len = 1;
	start = *i;
	(*i)++;
	while (!ft_strchr(" \t\\\'\"/$", (*line)[*i]))
	{
		len++;
		(*i)++;
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
	int	quotes;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			quotes_one(&line, &i);
		else if (line[i] == '\"')
			quotes_dbl(&line, &i, env, status);
		else if(line[i] == '\\')
			bslash_proc(&line, &i);
		else if (line[i] == '$')
			dollar_proc(&line, &i, env, status);
		else
			i++;
	}
	return (line);
}

// int main()
// {
// 	char *line = strdup("  sd$hello  \'$PWD\' word");
// 	line = parce_line(line);
// 	printf("%s\n", line);
// 	free(line);
// 	sleep(1000);
// 	return 0;
// }