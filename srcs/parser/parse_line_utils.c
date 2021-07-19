#include "parser.h"

char	*str_replace(char *line, int start, int len, char *replace)
{
	char	*left;
	char	*right;
	char	*tmp;

	left = ft_substr(line, 0, start);
	right = ft_strdup(line + start + len);
	if (!left && !right)
		exit(msh_strerror(EXIT_FAILURE));
	free(line);
	tmp = left;
	left = ft_strjoin(left, replace);
	free(tmp);
	if (!left)
		exit(msh_strerror(EXIT_FAILURE));
	tmp = left;
	left = ft_strjoin(left, right);
	free(tmp);
	free(right);
	if (!left)
		exit(msh_strerror(EXIT_FAILURE));
	return (left);
}
