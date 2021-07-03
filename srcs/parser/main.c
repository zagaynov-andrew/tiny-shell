#include "parser.h"
#include "test_list/test_minishell.h"

void print_list(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", ((char **)(tmp->content))[0]);
		tmp = tmp->next;
	}
}

int main()
{
	char *str = "<<ls -la \"ab cd\"|cat FILE<< file1";
	char **split;
	int status = 0;
	t_list *list;
	split = ft_split_cmd_args(str);
	// while (*split)
	// printf("%s\n", *split++);
	list = NULL;
	list = lexer(str, status);
	// print_list(list);
	print_list_str_array(list);
	return (0);
}