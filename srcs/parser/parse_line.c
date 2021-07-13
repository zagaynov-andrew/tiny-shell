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

static char *parser_dollar(char *line, int *i, char **env, int status)
{
	char	*tmp1;
	char	*tmp2;
	int		siz;
	int		j;
	int		len;

	j = *i;
	(*i)++;
	len = 0;
	while ((line[*i] == '_' || ft_isalnum(line[*i])) && !ft_isdigit(line[j + 1]))
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return (line);
	tmp1 = ft_substr(line, j + 1, len);
	tmp1 = check_var(tmp1, env, status);
	siz = ft_strlen(line) - ft_strlen(&line[j]);
	tmp2 = malloc(ft_strlen(tmp1) + ft_strlen(&line[*i]) + ft_strlen(tmp1) + siz);
	ft_strncpy(tmp2, line, ft_strlen(line) - ft_strlen(&line[j]));
	ft_strncpy(&tmp2[j], tmp1, ft_strlen(tmp1));
	ft_strncpy(&tmp2[j + ft_strlen(tmp1)], &line[j + 1 + len], ft_strlen(line));
	free(tmp1);
	free(line);
	*i = j + ft_strlen(tmp1);
	return (tmp2);
}

static char *parce_sl_dl(char *line, char **env, int status)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
			line = parse_slash(line, &i);
		else if (line[i] == '$')
			line = parser_dollar(line, &i, env, status);
		else
			i++;
	}
	return (line);
}

static char	*remove_quote(char *line)
{
	char *tmp;

	tmp = malloc(ft_strlen(line) - 2);
	if (!tmp)
	{
		perror("Error one quote malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(tmp, (line + 1), ft_strlen(line) - 2);
	free(line);
	return (tmp);
}

char	*parce_line(char *line, char **env, int status)
{
	if (*line == '\'')
		line = remove_quote(line);
	else if (*line == '\"')
	{
		line = remove_quote(line);
		line = parce_sl_dl(line, env, status);
	}
	else
		line = parce_sl_dl(line, env, status);
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