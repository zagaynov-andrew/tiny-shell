#include "parser.h"

int	count_quotes(char *line, int *i)
{
	char	ch;

	ch = line[*i];
	(*i)++;
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

char	first_token_symbol(char *line, int i)
{
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	return (line[i]);
}
