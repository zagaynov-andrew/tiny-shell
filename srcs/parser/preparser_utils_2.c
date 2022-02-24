#include "parser.h"

static char	*define_del_utils(char *str, char *operator)
{
	free(str);
	return (operator);
}

char	*define_del(char *str)
{
	if (!str)
		exit(msh_strerror(EXIT_FAILURE));
	if (!ft_strcmp("|", str))
		return (define_del_utils(str, "|"));
	if (!ft_strcmp("<<", str))
		return (define_del_utils(str, "<<"));
	if (!ft_strcmp(">>", str))
		return (define_del_utils(str, ">>"));
	if (!ft_strcmp("<", str))
		return (define_del_utils(str, "<"));
	if (!ft_strcmp(">", str))
		return (define_del_utils(str, ">"));
	free(str);
	return (NULL);
}

static int	checking_token_after(char *line, int i, char *token)
{
	if (!token)
		return (1);
	if (is_redir(token) && ft_strchr("<>|", first_token_symbol(line, i)))
		return (1);
	if (!ft_strcmp(token, "|") && first_token_symbol(line, i) == '|')
		return (1);
	return (0);
}

static int	checking_redir_pipes(char *line, int i, int len)
{
	int		start;
	char	*token;

	if (first_token_symbol(line, i) == '|')
		return (msh_perror("syntax error near unexpected token", 1));
	while (line[i])
	{
		len = 0;
		if (ft_strchr("<>|", line[i]))
		{
			start = i;
			while (line[i] && ft_strchr("<>|", line[i]))
			{
				len++;
				i++;
			}
			token = define_del(ft_substr(line, start, len));
			if (checking_token_after(line, i, token))
				return (msh_perror("syntax error near unexpected token", 1));
		}
		else
			i++;
	}
	return (0);
}

int	check_redir_pipes(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	return (checking_redir_pipes(line, i, len));
}
