#include "parser.h"

int	ft_comp_cmd(char *cmd, char *d_name)
{
	char	*tmp;

	tmp = ft_tolower_line(ft_strdup(cmd));
	if (!tmp)
		ft_strerror("Bad malloc allocation\n");
	if (!ft_strcmp(tmp, d_name))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	*file_path(char *d_name, char *dir, char *cmd)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("/", d_name);
	tmp2 = tmp1;
	tmp1 = ft_strjoin(dir, tmp1);
	free(tmp2);
	free(cmd);
	if (!tmp1)
		ft_strerror("Error strjoin\n");
	return (tmp1);
}

char	**split_path(char *path, char **env)
{
	char	**splitpath;
	char	*tmp;

	tmp = get_env_var_value(path, (const char **)env);
	splitpath = ft_split(tmp, ':');
	free(tmp);
	if (!splitpath)
		ft_strerror("Path split error\n");
	return (splitpath);
}

char	*ft_tolower_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		line[i] = ft_tolower(line[i]);
		i++;
	}
	return (line);
}
