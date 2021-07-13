#include "parser.h"

int		length_data(char **split)
{
	int len;

	len = 0;
	if (ft_strchr("|", **split))
		return (1);
	while (*split)
	{
		if (!ft_strchr("|", **split))
			len++;
		else
			break;
		split++;
	}
	return (len);
}

char	*create_row(char **split)
{
	char	*tmp;

	tmp = malloc(sizeof(char *) * ft_strlen(*split) + 1);
	if (!tmp)
	{
		perror("Error malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(tmp, *split, ft_strlen(*split));
	return (tmp);
}

t_list	*create_node(char **data, t_list *node)
{
	node = ft_lstnew((void *)data);
	if (!node)
	{
		perror("Error malloc node");
		exit(EXIT_FAILURE);
	}
	return (node);
}

t_list	*make_node(char **split)
{
	int		len;
	char	**data;
	int		i;
	t_list	*node;
	
	len = 0;
	i = 0;
	node = NULL;
	if (!ft_strchr("<>|\'\"", **split))
	{
		len = length_data(split);
		data = malloc(sizeof(char *) * len + 1);
		while (*split && !ft_strchr("|", **split))
			data[i++] = create_row(split++);
		data[i] = 0;
		return (create_node(data, node));
	}
	else if (ft_strchr("<>", **split))
	{
		len = length_data(split);
		data = malloc(sizeof(char *) * len + 1);
		data[i++] = create_row(split++);
		while (*split && !ft_strchr("|", **split))
			data[i++] = create_row(split++);
		data[i] = 0;
		return (create_node(data, node));
	}
	else
	{
		data = malloc(sizeof(char *) * 2);
		data[i++] = create_row(split);
		data[i] = 0;
		return (create_node(data, node));
	}
		return (NULL);
}

void	make_cmd_table(t_list **list, char **split)
{
	t_list	*new;

	while (*split)
	{
		new = make_node(split);
		split += length_data(split) - 1;
		ft_lstadd_back(list, new);
		split++;
	}
}

t_list *cmd_table(char **split)
{
	t_list *lst;

	lst = NULL;
	make_cmd_table(&lst, split);
	return (lst);
}