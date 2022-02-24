#include "tinylibc.h"

int	ft_strlen(const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}
