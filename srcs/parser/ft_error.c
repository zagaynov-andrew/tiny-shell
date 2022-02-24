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
	str = "tinyshell: syntax error near unexpected token";
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
