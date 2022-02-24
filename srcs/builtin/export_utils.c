#include "builtin.h"

void	print_not_valid(const char *var)
{
	ft_putstr_fd("tinyshell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	msh_export_print(const char **str_array)
{
	int	i;
	int	j;

	i = 0;
	while (str_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (str_array[i][j] != '=' && str_array[i][j] != '\0')
		{
			ft_putchar_fd(str_array[i][j], 1);
			j++;
		}
		if (str_array[i][j] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(&str_array[i][j + 1], 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
