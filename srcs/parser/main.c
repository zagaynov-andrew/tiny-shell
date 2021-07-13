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

int main(int arc, char **argv, char **env)
{
	if(arc != 1)
		return 0;
	(void)argv;
	char *str = "\t \r cat \"hello \'\t \r$PWD\' world\"< $PWD pwd | CAT FILE<< file1";
	char **split;
	int status = 0;
	t_list *list;
	split = ft_split_cmd_args(str);
	while (*split)
	printf("%s\n", *split++);
	list = NULL;
	list = lexer(str, status, env);
	print_list_str_array(list);
	ft_lstclear1(&list, del_list_content);
	// sleep(1000);
	// printf("%s\n", str);
	return (0);
}