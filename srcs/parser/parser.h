#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "libft/libft.h"

t_list  *lexer(char *line, int status, char **env);
void    skip_wsp(int *i, char *line);
void    skip_del_ch(char *line, int *len, int *i);
int     get_num_words(char *line);
int     quote_len(char *line, char ch);
void    quote_parse(char **split, char **line, int *i);
char    **ft_split_cmd_args(char *line);
t_list  *cmd_table(char **split);
char    *check_var(char *line, char **env, int status);
void    del_list_content(void *data);
void    ft_lstclear1(t_list **lst, void (*del)(void *));
void    free_split(char **split);
void    ft_strerror(char *str);
char    *check_cmd(char *cmd, char **env);
char    *parce_line(char *line, char **env, int status);
char    *get_env_var_value(char *name, char **env);
#endif