#ifndef TEST_TINYSHELL_H
# define TEST_TINYSHELL_H

# include <stdio.h>
# include "../../libs/tinylibc/tinylibc.h"

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define PURPLE	"\033[1;35m"

void	print_str_array(char **array);
void	print_list_str_array(t_list *lst);
void	print_str_array_no_color(char **array);

#endif
