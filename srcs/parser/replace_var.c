#include "parser.h"

char	*replace_var(char *name, char **env, int status)
{
	char	*str_new;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(status));
	str_new = get_env_var_value(name, env);
	return (str_new);
}
