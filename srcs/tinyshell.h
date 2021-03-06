#ifndef TINYSHELL_H
# define TINYSHELL_H

# define OUT_FILE		0
# define OUT_APP_FILE	1
# define IN_FILE		2
# define HEREDOC		3

# include "executor/executor.h"
# include "test/test_tinyshell.h"
# include "../libs/tinylibc/tinylibc.h"
# include "parser/parser.h"
# include <readline/readline.h>
# include <readline/history.h>

int		g_last_exit_status;

void	void_array_free(void *void_array);
int		split_shell_lst_element(char *element[],
			t_list **cmd_lst, t_list **redir_lst);
int		split_lst_cmds_redirs(t_list *shell_lst,
			t_list **cmds, t_list **redirs);
int		msh_exit_error(int ret);
int		msh_perror(char *str, int ret);
int		msh_perror_arg(char *arg, char *str, int ret);
int		msh_strerror(int ret);
int		msh_strerror_arg(int ret, char *arg);
int		msh_strerror_arg_2(int ret, char *arg_1, char *arg_2);
void	sig_catcher_msh(int sig);
void	sig_catcher_cmds(int sig);
void	sig_catcher_heredoc(int sig);
void	init_signals(void (*sig_catcher)(int));
char	*msh_heredoc(char *delimeter);
void	fill_cmd(char *element[], t_list **cmd_lst);
void	fill_redir(char *element[], t_list **redir_lst);
void	prompt_loop(t_list	**cmds, t_list **redirs,
			char **env_copy[], t_list **shell_lst);
void	split_shell_lst(t_list *shell_lst, t_list **cmds, t_list **redirs);
int		clear_shell_lst(t_list **shell_lst, t_list **cmds,
			t_list **redirs, char **input);
void	add_to_history(char *input);
void	set_env_var(char *env_str, char **env[]);
int		check_redir_pipes(char *line);

#endif
