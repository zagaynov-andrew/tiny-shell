#include "builtin.h"

static int	is_number(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
	{
		if (!ft_isdigit(str[1]))
			return (0);
		str += 2;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	get_exit_status(char *status)
{
	int	int_status;

	int_status = ft_atoi(status);
	if (int_status >= 0)
		return (int_status % 256);
	while (int_status < 0)
		int_status += 256;
	return (int_status);
}

int	msh_exit(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)env;
	if (str_array_size((const char **)argv) > 1)
	{
		if (!is_number(argv[1]))
		{
			ft_putstr_fd("exit\n", 2);
			g_last_exit_status = msh_perror_arg(argv[1],
					": numeric argument required", 255);
			return (-2);
		}
	}
	if (str_array_size((const char **)argv) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		return (msh_perror("exit: too many arguments", 1));
	}
	if (str_array_size((const char **)argv) == 2)
	{
		g_last_exit_status = msh_exit_error(get_exit_status(argv[1]));
		return (-2);
	}
	g_last_exit_status = msh_exit_error(0);
	return (-2);
}
