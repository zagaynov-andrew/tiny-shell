#include "parser.h"

char	*checking_cmd(DIR *dir, char *path, char **cmd)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (ft_comp_cmd(*cmd, entry->d_name))
		{
			*cmd = file_path(entry->d_name, path, *cmd);
			return (*cmd);
		}
		entry = readdir(dir);
	}
	return (NULL);
}

char	*check_cmd(char *cmd, char **env)
{
	DIR				*dir;
	char			**tmp_split;
	char			**splitpath;

	splitpath = split_path("PATH", env);
	tmp_split = splitpath;
	while (*splitpath)
	{
		dir = opendir(*splitpath);
		if (!dir)
		{
			splitpath++;
			continue ;
		}
		if (checking_cmd(dir, *splitpath, &cmd))
		{
			closedir(dir);
			str_array_free(&tmp_split);
			return (cmd);
		}
		closedir(dir);
		splitpath++;
	}
	str_array_free(&tmp_split);
	return (cmd);
}
