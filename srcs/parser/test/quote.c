#include "parser.h"

char *fill_back(char *line, char *new, int nm)
{
	int i;

	ft_strncpy(new, line, ft_strlen(line));
	i = ft_strlen(line);
	while (i < nm + (int)ft_strlen(line))
		new[i++] = ' ';
	new[i] = '\0';
	return (new);
}

char *fill_forward(char *line, char *new, int nm)
{
	int i;

	i = 0;
	while (i < nm)
		new[i++] = ' ';
	ft_strncpy(new + nm, line, ft_strlen(line));
	return (new);
}

void ft_join_spaces(char **line, int nm, char ch)
{
	char *new_line;

	if (nm <= 0 && !*line)
		return;
	new_line = malloc(nm + ft_strlen(*line) + 1);
	if (!new_line)
	{
		perror("Error join_spaces malloc");
		exit(EXIT_FAILURE);
	}
	if (ch == 'b')
		new_line = fill_back(*line, new_line, nm);
	else if (ch == 'f')
		new_line = fill_forward(*line, new_line, nm);
	free(*line);
	*line = new_line;
}

char *ft_join_word(char *line, char **split)
{
	char *new_line;

	new_line = ft_strjoin(line, *split);
	if (!new_line)
		ft_strerror("Error strjoin(line, spaces)\n");
	free(line);
	return (new_line);
}

int		count_nmb(char *line)
{
	int count;

	count = 0;
	while (*line == ' ')
	{
		count++;
		line++;
	}
	return (count);
}

char *ft_split_join(char *line, char **split)
{
	int nmb_spaces;
	char *str;
	int sp;

	str = *split;
	sp = 0;
	nmb_spaces = count_nmb(line);
	while (*line == ' ')
	{
		line++;
		sp++;
	}
	ft_join_spaces(&str, sp, 'f');
	line += ft_strlen(*split);
	split++;
	while (*split)
	{
		nmb_spaces = count_nmb(line);
		ft_join_spaces(&str, nmb_spaces, 'b');
		str = ft_join_word(str, split);
		line += nmb_spaces;
		while (*line && *line != ' ')
			line++;
		split++;
	}
	return (str);
}

void	parce_dbl_quote(char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i])
	{
		split[i] = check_var(split[i]);
		i++;
	}
	line = ft_split_join(line, split);
}

void	parce_one_quote(char *line)
{
	char	*tmp;

	tmp = malloc(ft_strlen(line) - 2);
	if (!tmp)
	{
		perror("Error one quote malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(tmp, (line + 1), ft_strlen(line) - 1);
	free(line);
	line = tmp;
}

void	quote(char *line) 
{
	if (*line == '\'')
		parce_one_quote(line);
	else if (*line == '\"')
		parce_dbl_quote(line);
}
