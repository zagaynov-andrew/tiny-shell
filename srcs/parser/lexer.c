#include "parser.h"

t_list *lexer(char *line, int status)
{
	t_list	*node;
	char	**split;

	if (status != 0)
		return (NULL);
	node = NULL;
	split = ft_split_cmd_args(line);
	node = cmd_table(split);
	return (node);
}
