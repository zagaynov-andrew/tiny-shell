#include "parser.h"

void	to_next_quote(int *i, char *line)
{
	char	ch;

	ch = line[*i];
	(*i)++;
	while (line[*i] != ch)
		(*i)++;
}

void	to_end_word(int *i, char *line)
{
	while (!ft_strchr(" \t|<>", line[*i]))
		(*i)++;
	(*i)--;
}
