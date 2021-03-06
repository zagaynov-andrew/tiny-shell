#include "builtin.h"

int	is_valid_env_name(const char *env_ptr)
{
	int		name_len;
	char	*equal;
	int		i;

	if (env_ptr[0] == '=')
		return (0);
	if (ft_isdigit(env_ptr[0]))
		return (0);
	equal = ft_strnstr(env_ptr, "=", ft_strlen(env_ptr));
	if (equal)
		name_len = equal - env_ptr;
	else
		name_len = ft_strlen(env_ptr);
	i = 0;
	while (i < name_len)
	{
		if (!ft_isalnum(env_ptr[i]) && env_ptr[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_env_pos(const char *name, const char **env)
{
	int		i;
	int		cur_name_len;
	int		name_len;
	char	*equal;

	equal = ft_strnstr(name, "=", ft_strlen(name));
	if (equal)
		name_len = equal - name;
	else
		name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		equal = ft_strnstr(env[i], "=", ft_strlen(env[i]));
		if (equal)
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

static char	*return_empty(void)
{
	char	*value;

	value = ft_strdup("");
	if (!value)
		exit(msh_strerror(EXIT_FAILURE));
	return (value);
}

char	*get_env_var_value(const char *name, const char **env)
{
	int		pos;
	char	*value;
	char	*equal;

	if (!name || !env)
		return (NULL);
	pos = get_env_pos(name, env);
	if (pos == -1)
		return (return_empty());
	equal = ft_strnstr(env[pos], "=", ft_strlen(env[pos]));
	if (!equal)
		return (return_empty());
	value = ft_strdup(equal + 1);
	if (!value)
		exit(msh_strerror(EXIT_FAILURE));
	return (value);
}
