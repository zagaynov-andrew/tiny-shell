#include "parser.h"

void	ft_strerror(char *str)
{
	write(1, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	ft_parse_error(char ch)
{
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	write(1, str, ft_strlen(str));
	write(1, "\'", 1);
	write(1, &ch, 1);
	write(1, "\'\n", 2);
}
