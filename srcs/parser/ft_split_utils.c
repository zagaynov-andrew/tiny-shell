#include "parser.h"

int	quote_len(char *line, char ch)
{
	int	len;
	int	i;
	int	count;

	len = 0;
	count = 0;
	i = 1;
	while (line[i] && line[i] != ch)
	{
		if (!ft_strchr(" \t \r \v", line[i]))
			count++;
		len++;
		i++;
	}
	return (len);
}

void	quote_parse(char **split, char **line, int *i)
{
	int		len;
	char	*tmp;

	len = quote_len(*line, **line);
	if (len == 0)
	{
		*line += len + 2;
		return ;
	}
	tmp = *line;
	split[*i] = malloc(sizeof(char) * len + 3);
	ft_strncpy(split[*i], tmp, len + 2);
	*i = *i + 1;
	*line += len + 2;
}

void	skip_wsp(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\r')
		(*i)++;
}

void	skip_del_ch(char *line, int *len, int *i)
{
	char	ch;

	(*len)++;
	ch = line[*i];
	while (line[*i] == ch)
		(*i)++;
}

int	get_num_words(char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			skip_wsp(&i, line);
		else if (ft_strchr("|<> ", line[i]))
			skip_del_ch(line, &len, &i);
		else if (line[i] == '\'' || line[i] == '\"')
		{
			i += quote_len(&line[i], line[i]) + 2;
			if (quote_len(&line[i], line[i]))
				len++;
		}
		else
		{
			len++;
			while (!ft_strchr("|<> ", line[i]))
				i++;
		}
	}
	return (len);
}
