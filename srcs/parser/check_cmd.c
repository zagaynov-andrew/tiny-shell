#include "parser.h"

char	*checking_cmd(DIR *dir, char *path, char **cmd, char **split)
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
	// struct dirent	*entry;
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
		// entry = readdir(dir);
		// while (entry)
		// {
		// 	if (ft_comp_cmd(cmd, entry->d_name))
		// 	{
		// 		cmd = file_path(entry->d_name, *splitpath, cmd);
		// 		str_array_free(&tmp_split);
		// 		closedir(dir);
		// 		return (cmd);
		// 	}
		// 	entry = readdir(dir);
		// }
		// closedir(dir);
		if (checking_cmd(dir, *splitpath, &cmd, tmp_split))
		{
			closedir(dir);
			str_array_free(&tmp_split);
			return (cmd);
		}
		splitpath++;
	}
	str_array_free(&tmp_split);
	return (cmd);
}
