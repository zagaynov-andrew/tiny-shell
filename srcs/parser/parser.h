#ifndef PARSER_H
# define PARSER_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include "gnl/get_next_line.h"
# include "../../libs/libft/libft.h"
# include "test_list/test_minishell.h"

t_list	*lexer(char *line, int status, char **env);
char	**ft_split_cmd_args(char *line);
t_list	*cmd_table(char **split);
void	del_list_content(void *data);
void	ft_lstclear1(t_list **lst, void (*del)(void *));
void	free_split(char **split);
void	ft_strerror(char *str);
char	*check_cmd(char *cmd, char **env);
char	*parce_line(char *line, char **env, int status);
char	*get_env_var_value(char *name, char **env);
void	insert_tokken(int *i, char ***split, char *line);
char	**str_array_add_back(char **str_array[], const char *str);
char	*str_replace(char *line, int start, int len, char *replace);
int		msh_strerror(int ret);
char	*replace_var(char *name, char **env, int status);
int		is_redir(char *str);
int		preparser(char *line);
void	ft_parse_error(char ch);
char	*ft_tolower_line(char *line);
char	*define_del(char *str);
int		check_quotes(char *line);
int		ft_comp_cmd(char *cmd, char *d_name);
char	*file_path(char *d_name, char *dir, char *cmd);
char	**split_path(char *path, char **env);
int		is_built_in(char *str);
char	*remove_q(char *str);
void	remove_quotes_fl(char **arr);
#endif