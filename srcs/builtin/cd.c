#include "builtin.h"

static int	cd_home(const char **env)
{
	char	*home;

	home = get_home(env);
	if (!home)
		return (1);
	if (chdir(home) != 0)
	{
		free (home);
		return (msh_perror("cd: HOME not set", EXIT_FAILURE));
	}
	free (home);
	return (0);
}

static int	cd_oldpwd(const char **env)
{
	char	*home;

	home = get_env_var_value("OLDPWD", env);
	if (!ft_strcmp(home, ""))
	{
		free(home);
		home = getenv("OLDPWD");
	}
	if (!home)
		return (1);
	if (chdir(home) != 0)
	{
		free(home);
		return (msh_perror("cd: HOME not set", EXIT_FAILURE));
	}
	free(home);
	return (0);
}

static int	msh_cd_utils_2(const char *argv[], char *oldpwd, const char *env[])
{
	char	*home;
	char	*path;

	home = get_home(env);
	if (!home)
	{
		free(oldpwd);
		return (msh_perror("cd: HOME not set", EXIT_FAILURE));
	}
	path = ft_strjoin(home, argv[1] + 1);
	if (!path)
		exit(msh_strerror(EXIT_FAILURE));
	free(home);
	if (chdir(path) == -1)
	{
		free(oldpwd);
		free(path);
		return (msh_strerror_arg_2(1, "cd", (char *)argv[1]));
	}
	free(path);
	return (0);
}

static int	msh_cd_utils(const char *argv[], char *oldpwd, const char *env[])
{
	if (argv[1][0] == '~')
	{
		if (msh_cd_utils_2(argv, oldpwd, env))
		{
			free(oldpwd);
			return (1);
		}
	}
	else if (chdir(argv[1]) == -1)
	{
		free(oldpwd);
		return (msh_strerror_arg_2(1, "cd", (char *)argv[1]));
	}
	return (0);
}

int	msh_cd(const int argc, const char *argv[], char **env[])
{
	char	*oldpwd;

	oldpwd = get_cur_dir_s((const char **)*env);
	if (argc == 1 || !ft_strcmp(argv[1], "~"))
	{
		if (cd_home((const char **)*env))
		{
			free(oldpwd);
			return (1);
		}
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "-"))
	{
		if (cd_oldpwd((const char **)*env))
		{
			free(oldpwd);
			return (1);
		}
	}
	else if (msh_cd_utils(argv, oldpwd, (const char **)*env))
		return (1);
	change_pwd_oldpwd(oldpwd, env);
	free(oldpwd);
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	char	**copy_env;

// 	copy_env = NULL;
// 	copy_env = str_array_copy((const char **)env);
// 	// str_array_ffree(copy_env);
// 	// copy_env = str_array_add_back(&copy_env, "pwd=string");
// 	// copy_env = str_array_add_back(&copy_env, "second=string");
// 	// copy_env = str_array_add_back(&copy_env, "OLDPWD=string");
// 	// copy_env = str_array_add_back(&copy_env, "PWD=string");
// 	// copy_env = str_array_add_back(&copy_env, "third=string");
// 	// copy_env = str_array_add_back(&copy_env, "forth=string");
//     msh_cd((const int)argc, (const char **)argv, &copy_env);
// 	char	*cur_dir = get_cur_dir();
// 	printf("PWD = %s\n", cur_dir);
// 	int	oldpwd_pos = get_env_pos("OLDPWD", (const char **)copy_env);
// 	int	pwd_pos = get_env_pos("PWD", (const char **)copy_env);
// 	printf("%s\n", copy_env[oldpwd_pos]);
// 	printf("%s\n", copy_env[pwd_pos]);
// 	free(cur_dir);
// 	str_array_free(copy_env);
//     return (0);
// }
