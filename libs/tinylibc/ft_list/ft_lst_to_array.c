#include "../tinylibc.h"

char	**ft_lst_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**array;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	array = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		array[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
