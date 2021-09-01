#include "parser.h"

int	is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "<<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}
