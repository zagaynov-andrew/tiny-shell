#include "builtin.h"

char	*get_cur_dir(void)
{
	int		size;
	char	*path;
	char	*tmp;

	size = 200;
	path = (char *)ft_calloc(size, sizeof(char));
	if (!path)
		exit(msh_strerror(EXIT_FAILURE));
	tmp = path;
	getcwd(path, size);
	if (!path && errno != 34)
		return (path);
	while (!path)
	{
		free(tmp);
		size *= 2;
		path = (char *)ft_calloc(size, sizeof(char));
		if (!path)
			exit(msh_strerror(EXIT_FAILURE));
		getcwd(path, size);
		if (!path && errno != 34)
			return (path);
	}
	errno = 0;
	return (path);
}

static int	msh_pwd_perror(char *arg_1, char c, char *arg_2, int ret)
{
	ft_putstr_fd(arg_1, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(arg_2, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	msh_pwd(int argc, char *argv[], char *env[])
{
	char	*cur_dir;

	(void)argc;
	(void)env;
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == '-'
			&& argv[1][2] != '\0')
			return (msh_pwd_perror("tinyshell: pwd: -",
					argv[1][1], ": invalid option", 1));
		else if (argv[1][0] == '-' && argv[1][1] != '\0'
			&& argv[1][1] != '-')
			return (msh_pwd_perror("tinyshell: pwd: -",
					argv[1][1], ": invalid option", 1));
	}
	cur_dir = get_cur_dir_s((const char **)env);
	if (!cur_dir)
		return (1);
	ft_putstr_fd(cur_dir, 1);
	ft_putchar_fd('\n', 1);
	free(cur_dir);
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_pwd(argc, argv, env);
// 	return (0);
// }
