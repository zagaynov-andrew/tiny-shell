#include "parser.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while ((split)[i])
		free((split)[i++]);
	free(split);
	split = NULL;
}

void del_list_content(void *data)
{
	free_split((char **)(&(((t_list *)(data))->content)));
}

void ft_lstclear1(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	while (*lst)
	{
		del((*lst)->content);
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
