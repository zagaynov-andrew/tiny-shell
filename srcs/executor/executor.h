#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../libs/tinylibc/tinylibc.h"
# include "../test/test_tinyshell.h"
# include "../builtin/builtin.h"
# include "../tinyshell.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NOT_FOUND ": command not found"

int		msh_exec(t_list *cmds, t_list *redirs, char **env[]);
void	pre_execution(t_list *shell_lst, t_list *redirs);
int		msh_launch(t_list *cmd, t_list **pid_lst, char **env[], int num_cmds);
int		set_input(char **redirs, int tmp[], int fd[]);
void	set_output(char **redirs, int tmp[], int fd[], int flag_last);
void	msh_create_pipe(int fd[]);
int		processint_pids(t_list **pid_lst, int status[]);
void	inc_shell_lvl(char *path, char **env[]);

#endif
