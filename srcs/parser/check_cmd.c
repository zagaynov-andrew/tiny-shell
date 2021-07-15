#include "parser.h"

int ft_comp_cmd(char *filename, char *cmd)
{
	if (ft_strlen(filename) == ft_strlen(cmd))
	{
		if (!ft_strncmp(filename, cmd, ft_strlen(cmd)))
			return (1);
	}
	return (0);
}

char **split_path(char *path, char **env)
{
	char	**splitpath;
	char	*tmp;

	tmp = get_env_var_value(path, env);
	splitpath = ft_split(tmp, ':');
	free(tmp);
	if (!splitpath)
		ft_strerror("Path split error\n");
	return (splitpath);
}

void ft_tolower_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		line[i] = ft_tolower(line[i]);
		i++;
	}
}

// DIR *ft_opendir(char *direct)
// {
// 	DIR *dir;

// 	dir = opendir(direct);
// 	if (!dir)
// 	{
// 		perror("diropen");
// 		exit(1);
// 	}
// 	return (dir);
// }

char *file_path(char *d_name, char *dir, char *cmd)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_strjoin("/", d_name);
	tmp2 = tmp1;
	tmp1 = ft_strjoin(dir, tmp1);
	free(tmp2);
	free(cmd);
	if (!tmp1)
		ft_strerror("Error strjoin\n");
	return (tmp1);
}

char *check_cmd(char *cmd, char **env)
{
	DIR *dir;
	struct dirent *entry;
	char **tmp_split;
	char **splitpath;

	splitpath = split_path("PATH", env);
	tmp_split = splitpath;
	ft_tolower_line(cmd);
	while (*splitpath)
	{
		dir = opendir(*splitpath);
		if (!dir)
		{
			splitpath++;
			continue;
		}
		entry = readdir(dir);
		while (entry)
		{
			if (ft_comp_cmd(cmd, entry->d_name))
			{
				cmd = file_path(entry->d_name, *splitpath, cmd);
				free_split(tmp_split);
				closedir(dir);
				return (cmd);
			}
			entry = readdir(dir);
		}
		closedir(dir);
		splitpath++;
	}
	free_split(tmp_split);
	return (cmd);
}