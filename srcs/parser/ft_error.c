#include "parser.h"

void	ft_strerror(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	ft_parse_error(char ch)
{
	char	*str;

	(void)ch;
	str = "minishell: syntax error near unexpected token ";
	write(2, str, ft_strlen(str));
	write(2, "\'", 1);
	write(2, "\'\n", 2);
}
