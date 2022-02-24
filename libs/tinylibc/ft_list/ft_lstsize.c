#include "../tinylibc.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		size;

	if (!lst)
		return (0);
	size = 1;
	current = lst;
	while (current->next)
	{
		current = current->next;
		size++;
	}
	return (size);
}
