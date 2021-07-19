#include "test_minishell.h"

void	print_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("%s%7i%s \"%s%s%s\"\n", RED, i, RESET, YELLOW, array[i], RESET);
		i++;
	}
}

void	print_str_array_no_color(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
