#include "builtin.h"

int	msh_echo(int argc, char *argv[], char *env[])
{
	int	i;
	int	flag_n;

	(void)argc;
	(void)argv;
	(void)env;
	flag_n = 0;
	i = 1;
	if (ft_strcmp(argv[1], "-n") == 0)
	{
		i = 2;
		flag_n = 1;
	}
	while (i < argc)
	{
		if (i != 1 && !(i == 2 && flag_n))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (!flag_n)
		ft_putchar_fd('\n', 1);
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
// 	msh_echo(argc, argv, env);
// 	return (0);
// }
