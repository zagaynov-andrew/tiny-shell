#include "parser.h"

int	check_last_slash(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] == '\\')
	{
		ft_parse_error('\0');
		return (1);
	}
	return (0);
}

int	check_redir_pipes1(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("<>|", line[i]))
		{
			while (line[i] && ft_strchr("<>|", line[i]))
				i++;
			while (line[i] && ft_strchr(" \t><|", line[i]))
				i++;
			if (!line[i])
			{
				ft_parse_error(line[i - 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	preparser(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_quotes(line))
			return (1);
		if (check_redir_pipes(line))
			return (1);
		if (check_redir_pipes1(line))
			return (1);
		if (check_last_slash(line))
			return (1);
		i++;
	}
	return (0);
}
