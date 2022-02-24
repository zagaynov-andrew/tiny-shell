#include "builtin.h"

int	msh_env(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	while (*env)
	{
		if (ft_strchr(*env, '='))
		{
			ft_putstr_fd(*env, 1);
			ft_putchar_fd('\n', 1);
		}
		env++;
	}
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_env(argc, argv, env);
// 	return (0);
// }
