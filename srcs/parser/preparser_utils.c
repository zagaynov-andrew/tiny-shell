#include "parser.h"

static char	*define_del_utils(char *str, char *operator)
{
	free(str);
	return (operator);
}

char	*define_del(char *str)
{
	if (!str)
		exit(msh_strerror(EXIT_FAILURE));
	if (!ft_strcmp("|", str))
		return (define_del_utils(str, "|"));
	if (!ft_strcmp("<<", str))
		return (define_del_utils(str, "<<"));
	if (!ft_strcmp(">>", str))
		return (define_del_utils(str, ">>"));
	if (!ft_strcmp("<", str))
		return (define_del_utils(str, "<"));
	if (!ft_strcmp(">", str))
		return (define_del_utils(str, ">"));
	free(str);
	return (NULL);
}

int	count_quotes(char *line, int *i)
{
	char	ch;
	int		quotes;

	ch = line[*i];
	(*i)++;
	quotes = 0;
	while (line[*i] && line[*i] != ch)
		(*i)++;
	if (line[*i])
		return (0);
	return (1);
}

int	check_quotes(char *line)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quotes = count_quotes(line, &i);
		if (quotes % 2)
		{
			ft_parse_error(line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
