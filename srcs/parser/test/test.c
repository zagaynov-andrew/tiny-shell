#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static char *ft_strjoin(char const *s1, char const *s2)
{
	char *strjoin;
	int i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	strjoin = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (strjoin)
	{
		while (*s1)
		{
			strjoin[i] = *s1++;
			i++;
		}
		while (*s2)
		{
			strjoin[i] = *s2++;
			i++;
		}
		strjoin[i] = '\0';
		return (strjoin);
	}
	return (NULL);
}

static int ft_length(const char *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static int ft_numstr(const char *s, char c, int numstr)
{
	int inword;

	inword = 1;
	if (s)
	{
		while (*s)
		{
			if (*s == c)
			{
				inword = 1;
				s++;
			}
			if (*s != c && *s)
			{
				if (inword)
				{
					numstr++;
					inword = 0;
				}
				s++;
			}
		}
		return (numstr);
	}
	return (0);
}

static char *ft_makestr(const char *s, char c)
{
	char *str;
	int len;
	int i;

	i = 0;
	len = ft_length(s, c);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

static char **ft_split_d(char **split, int numstr,
						 char c, const char *s)
{
	int i;

	i = 0;
	while (i < numstr && *s)
	{
		if (*s == c)
			s++;
		else
		{
			split[i] = ft_makestr(s, c);
			if (!split[i])
			{
				while (i >= 0)
					free(split[i--]);
				free(split);
				return (NULL);
			}
			s = s + ft_length(s, c);
			i++;
		}
	}
	split[i] = 0;
	return (split);
}

static char **ft_split(char const *s, char c)
{
	char **split;
	int numstr;
	int i;

	i = 0;
	numstr = 0;
	if (!s)
		return (NULL);
	numstr = ft_numstr(s, c, numstr);
	split = (char **)malloc(sizeof(char *) * (numstr + 1));
	if (!split)
		return (NULL);
	return (ft_split_d(split, numstr, c, s));
}

static void ft_strncpy(char *dst, char *src, int n)
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

static int count_nmb(char *line)
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

static char *fill_back(char *line, char *new, int nm)
{
	int i;

	ft_strncpy(new, line, ft_strlen(line));
	i = ft_strlen(line);
	while (i < nm + ft_strlen(line))
		new[i++] = ' ';
	new[i] = '\0';
	return (new);
}

static char *fill_forward(char *line, char *new, int nm)
{
	int i;

	i = 0;
	while (i < nm)
		new[i++] = ' ';
	ft_strncpy(new + nm, line, ft_strlen(line));
	return (new);
}

static void ft_join_spaces(char **line, int nm, char ch)
{
	char *new_line;
	// int i;

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
	// ft_strncpy(new_line, *line, ft_strlen(*line));
	// i = ft_strlen(*line);
	// while (i < nm + ft_strlen(*line))
	// 	new_line[i++] = ' ';
	// new_line[i] = '\0';
	// free(*line);
	*line = new_line;
}

static char *ft_join_word(char *line, char **split)
{
	char *new_line;

	new_line = ft_strjoin(line, *split);
	// 	if (!new_line)
	// 		ft_strerror("Error strjoin(line, spaces)\n");
	// 	free(line);
	return (new_line);
}

static char *ft_split_join(char *line, char **split)
{
	int		nmb_spaces;
	char	*str;
	int		sp;

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
		while (*line != ' ')
			line++;
		split++;
	}
	return (str);
}

static char *check_var(char *line)
{
	char *tmp;
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			free(line);
			tmp = strdup("hi");
			return (tmp);
		}
		i++;
	}
	return line;
}

static char *parce_dbl_quote(char *line)
{
	char **split;
	int i;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i])
	{
		split[i] = check_var(split[i]);
		i++;
	}
	line = ft_split_join(line, split);
	return (line);
}

int main()
{
	char *line = strdup("  $hello $PWD  word");
	char **split = ft_split(line, ' ');
	line = parce_dbl_quote(line);
	printf("%s\n", line);
	return 0;
}