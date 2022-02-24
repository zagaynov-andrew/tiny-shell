#include "tinyshell.h"

void	void_array_free(void *void_array)
{
	int		i;
	char	**tmp;

	if (!void_array)
		return ;
	i = 0;
	tmp = (char **)void_array;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(void_array);
}

void	split_shell_lst(t_list *shell_lst, t_list **cmds, t_list **redirs)
{
	char	**str_array;
	int		i;

	*cmds = NULL;
	*redirs = NULL;
	i = 0;
	while (shell_lst)
	{
		str_array = (char **)shell_lst->content;
		if (i % 3 == 0)
			fill_cmd(str_array, cmds);
		if (i % 3 == 1)
			fill_redir(str_array, redirs);
		shell_lst = shell_lst->next;
		i++;
	}
}
