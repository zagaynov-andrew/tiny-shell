#include "parser.h"

char	*define_del(char *str, int len)
{
	if (!ft_strncmp("|", str , 1) && len == 1)
		return ("|");
	if (!ft_strncmp("<<", str, 2) && len == 2)
		return ("<<");
	if (!ft_strncmp(">>", str, 2) && len == 2)
		return (">>");
	if (!ft_strncmp("<", str, 1) && len == 1)
		return ("<");
	if (!ft_strncmp(">", str, 1) && len == 1)
		return (">");
	return (NULL);
}

int		calc_ch(char *str, char *ch)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(ch, str[i]))
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}

void	check_spec(char **split, char **line, int *i)
{
	int 	len;
	char	*type;

	len = calc_ch(*line, "|<>");
	type = define_del(*line, len);
	if (type)
	{
		split[*i] = malloc(sizeof(char) * ft_strlen(type) + 1);
		ft_strncpy(split[*i], type, ft_strlen(type));
		*i = *i + 1;
		(*line) += len;
	}
	else
	{
		write(1, "Error parsing delimetrs\n", 24);
		exit(EXIT_FAILURE);
	}
}

void	skip_spaces(char **line)
{
	while ((**line == ' ' || **line == '\t' || **line == '\r') && **line)
		(*line)++;
}

void	make_word(char **split, char **line, int *i)
{
	char	*tmp;
	int		len;

	tmp = *line;
	len = 0;
	while (!ft_strchr("|<> \'\"", **line))
	{
		(*line)++;
		len++;
	}
	split[*i] = malloc(sizeof(char) * len + 1);
	ft_strncpy(split[*i], tmp, len);
	*i = *i + 1;
}

char	**ft_split_cmd_args(char *line)
{
	int i;
	int numstr;
	char **split;

	i = 0;
	numstr = get_num_words(line);
	split = (char **)malloc(sizeof(char *) * numstr + 1);
	while (*line && i < numstr)
	{
		if (ft_strchr("|<>", *line))
			check_spec(split, &line, &i);
		else if (*line == ' ' || *line == '\t' || *line == '\r')
			skip_spaces(&line);
		else if (*line == '\'' || *line == '\"')
			quote_parse(split, &line, &i);
		else
			make_word(split, &line, &i);
	}
	split[i] = 0;
	return (split);
}
