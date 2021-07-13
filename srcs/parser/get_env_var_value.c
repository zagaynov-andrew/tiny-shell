#include "parser.h"

int	get_env_pos(char *name, char **env)
{
	int		i;
	int		cur_name_len;
	int		name_len;
	char	*equal;

	if ((equal = ft_strnstr(name, "=", ft_strlen(name))))
		name_len = equal - name;
	else
		name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((equal = ft_strnstr(env[i], "=", ft_strlen(env[i]))))
			cur_name_len = equal - env[i];
		else
			cur_name_len = ft_strlen(env[i]);
		if (name_len == cur_name_len
					&& ft_strncmp(env[i], name, cur_name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var_value(char *name, char **env)
{
	int		pos;
	char	*value;
	char	*equal;

	if (!name || !env)
		return (NULL);
	pos = get_env_pos(name, env);
	if (pos == -1)
		return (NULL);
	equal = ft_strnstr(env[pos], "=", ft_strlen(env[pos]));
	if (!equal)
		return (NULL);
	value = ft_strdup(equal + 1);
	return (value);
}
