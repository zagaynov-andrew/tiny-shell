#include "executor.h"

static void	inc_lst(t_list **cmds, t_list **redirs)
{
	*redirs = (*redirs)->next;
	*cmds = (*cmds)->next;
}

static int	msh_simple_cmd_loop(t_list *cmds, t_list *redirs,
			int std_io[], char **env[])
{
	int		num_cmds;
	int		i;
	int		fd[2];
	t_list	*pid_lst;
	int		status[2];

	set_input((char **)(redirs->content), std_io, fd);
	num_cmds = ft_lstsize(cmds);
	pid_lst = NULL;
	i = -1;
	while (++i < num_cmds)
	{
		if (i != num_cmds - 1)
			msh_create_pipe(fd);
		set_output(((char **)redirs->content), std_io, fd, i == num_cmds - 1);
		status[0] = msh_launch(cmds, &pid_lst, env, num_cmds);
		if (i != num_cmds - 1)
			status[0] = -1;
		inc_lst(&cmds, &redirs);
		if (i != num_cmds - 1)
			if (set_input((char **)(redirs->content), NULL, fd))
				i++;
	}
	return (processint_pids(&pid_lst, status));
}

int	msh_exec(t_list *cmds, t_list *redirs, char **env[])
{
	int	std_io[2];

	std_io[0] = dup(0);
	std_io[1] = dup(1);
	if (msh_simple_cmd_loop(cmds, redirs, std_io, env) == 1)
		return (1);
	dup2(std_io[0], 0);
	dup2(std_io[1], 1);
	close(std_io[0]);
	close(std_io[1]);
	return (0);
}
