#include "parser.h"

void	ft_strerror(char *str)
{
	write(1, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}