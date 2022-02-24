#include "str_array.h"

size_t	str_array_size(const char *str_array[])
{
	size_t	size;

	if (!str_array)
		return (0);
	size = 0;
	while (str_array[size])
		size++;
	return (size);
}
