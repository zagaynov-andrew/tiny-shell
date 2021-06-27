#include <stdio.h>
#include "../libft/libft.h"
#include <sys/wait.h>
#include <readline/history.h>

t_list	*parse_cmd(char *cmd)
{
	t_list	*args;

	args = NULL;
	ft_lstadd_back(&args, ft_lstnew((void*)ft_strdup("/bin/pwd")));
	return (args);
}

int		msh_launch(char *args[], char *env[])
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if ((pid = fork()) == 0)
	{
		if (execve(args[0], args, env) == -1)
			printf("EXIT_FAILURE\n");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (pid < 0)
	{
		// Ошибка при форкинге
	}
	return (0);
}

int		msh_exec(char *args[], char *env[])
{
	msh_launch(args, env);
	printf("%sDo smthng%s\n", "\033[1;33m", "\033[0m");
	return (0);
}

void	msh_loop(char *env[])
{
	t_list	*lst;
	char	**args;
	int		status;
	int		i;

	status = 0;
	while (!status)
	{
		lst = parse_cmd("command");
		args = ft_lst_to_array(lst);
		
		status = msh_exec(args, env);
		ft_lstclear(&lst, free);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	msh_loop(env);


	// int pipe_1[2];
	// int pipe_2[2];
	// char *yes[2];
	// char *head[2];
	// yes[0] = "/usr/bin/yes";
	// yes[1] = 0;
	// head[0] = "/usr/bin/head";
	// head[1] = 0;
	// pipe(pipe_1);
	// if (!fork())
	// {
	// 	dup2(pipe_1[0], 0);
	// 	close(pipe_1[1]);
	// 	close(pipe_1[0]);
	// 	execve(head[0], head, env);
	// }
	// close(pipe_1[0]);
	// pipe(pipe_2);
	// if (!fork())
	// {
	// 	dup2(pipe_2[1], 1);
	// 	close(pipe_2[1]);
	// 	close(pipe_2[0]);
	// 	execve(yes[0], yes, env);
	// }
	// close(pipe_2[1]);
	// wait(0);
	// wait(0);

	return (0);
}
