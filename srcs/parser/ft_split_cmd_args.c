#include "parser.h"

void	delimitres(int *i, char *line)
{
	char	ch;

	ch = line[*i];
	while (line[*i] == ch)
		(*i)++;
}

void	to_next_quote(int *i, char *line)
{
	char ch;

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

void	insert_tokken(int *i, char ***split, char *line)
{
	int start;
	int end;
	char	*tokken;

	start = *i;
	if (ft_strchr("|<>", line[*i]))
		delimitres(i, line);
	else if (line && line[*i] && !ft_strchr(" \t|<>", line[*i]))
	{
		while (line && line[*i] && !ft_strchr(" \t|<>", line[*i]))
		{
			if (line[*i] == '\'' || line[*i] == '\"')
				to_next_quote(i, line);
			else
				to_end_word(i, line);
			(*i)++;
		}
	}
	else if (ft_strchr("|<>", line[*i]))
		delimitres(i, line);
	end = *i - 1;
	tokken = ft_substr(line, start, end - start + 1);
	str_array_add_back(split, tokken);
	free(tokken);
}

char	**ft_split_cmd_args(char *line)
{
	int i;
	char **split;
	int quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	split = NULL;
	while (line && line[i])
	{
	
		if (!ft_is_whitespace(line[i]))
			insert_tokken(&i, &split, line);
		else
			i++;
	}
	// print_str_array(split);
	return (split);
}
