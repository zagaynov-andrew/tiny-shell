#include "test_minishell.h"

void	print_list_str_array(t_list *lst)
{
	int i;

	if (!lst)
		return ;
    printf("%s▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼%s\n", YELLOW, RESET);
    i = 0;
	while (lst)
	{
        printf(" ELEMENT %s%i%s:\n", PURPLE, i, RESET);
        print_str_array((char**)lst->content);
		i++;
        lst = lst->next;
	}
    printf("%s▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲%s\n", YELLOW, RESET);
}
