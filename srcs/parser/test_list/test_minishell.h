#ifndef TEST_MINISHELL_H
# define TEST_MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define PURPLE	"\033[1;35m"

void	print_str_array(char **array);
void	print_list_str_array(t_list *lst);

#endif
