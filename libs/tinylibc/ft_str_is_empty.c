#include "tinylibc.h"

int	ft_str_is_empty(char *str)
{
	if (!str)
		return (1);
	else if (*str == '\0')
		return (1);
	else
		return (0);
}
