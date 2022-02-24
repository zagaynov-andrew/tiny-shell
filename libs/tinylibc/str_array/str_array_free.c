#include "str_array.h"

char	**str_array_free(char **str_array[])
{
	int	i;

	if (!*str_array)
		return (NULL);
	i = 0;
	while ((*str_array)[i])
	{
		free((*str_array)[i]);
		i++;
	}
	free(*str_array);
	*str_array = NULL;
	return (NULL);
}
