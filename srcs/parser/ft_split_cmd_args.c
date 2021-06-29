#include "parser.h"

char	*define_del(char *str, int len)
{
	if (!ft_strncmp("|", str , 1) && len == 1)
		return ("PIPE");
	if (!ft_strncmp("<<", str, 2) && len == 2)
		return ("LESSLESS");
	if (!ft_strncmp(">>", str, 2) && len == 2)
		return ("GREATGREAT");
	if (!ft_strncmp("<", str, 1) && len == 1)
		return ("LESS");
	if (!ft_strncmp(">", str, 1) && len == 1)
		return ("GREAT");
	return (NULL);
}

void	ft_strncpy(char *dst, char *src, int n)
{
	int i;

	i = 0;
	while (src[i] && n)
	{
		dst[i] = src[i];
		n--;
		i++;
	}
	dst[i] = '\0';
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
		write(1, "Error parsing\n", 14);
		exit(EXIT_FAILURE);
	}
}

void	skip_spaces(char **line)
{
	while (**line == ' ' && **line)
		(*line)++;
}

void	make_word(char **split, char **line, int *i)
{
	char	*tmp;
	int		len;

	tmp = *line;
	len = 0;
	while (!ft_strchr("|<> ", **line))
	{
		(*line)++;
		len++;
	}
	split[*i] = malloc(sizeof(char) * len + 1);
	ft_strncpy(split[*i], tmp, len);
	*i = *i + 1;
}

int		get_num_words(char *line)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
		}
		else if (ft_strchr("|<> ", line[i]))
		{
			len++;
			while (ft_strchr("|<> ", line[i]))
				i++;
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
		else if (*line == ' ')
			skip_spaces(&line);
		else
			make_word(split, &line, &i);
	}
	split[i] = 0;
	return (split);
}
