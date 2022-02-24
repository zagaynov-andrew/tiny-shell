#include "tinyshell.h"

int	msh_perror(char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("tinyshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

int	msh_perror_arg(char *arg, char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("tinyshell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}
