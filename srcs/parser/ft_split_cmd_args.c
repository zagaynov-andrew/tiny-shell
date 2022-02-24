#include "parser.h"

void	delimitres(int *i, char *line)
{
	char	ch;

	ch = line[*i];
	while (line[*i] == ch)
		(*i)++;
}

void	insert_tokken_utils(char **split)
{
	if (!split)
		exit(msh_strerror(EXIT_FAILURE));
}

void	insert_tokken(int *i, char ***split, char *line)
{
	int		start;
	int		end;
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
	insert_tokken_utils(*split);
	free(tokken);
}

char	**ft_split_cmd_args(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = NULL;
	while (line && line[i])
	{
		if (!ft_is_whitespace(line[i]))
			insert_tokken(&i, &split, line);
		else
			i++;
	}
	return (split);
}
