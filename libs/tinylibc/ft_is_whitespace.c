#include "tinylibc.h"

int	ft_is_whitespace(char c)
{
	if (ft_char_in_set(" \t", c))
		return (1);
	return (0);
}
