#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../libs/tinylibc/tinylibc.h"
# include "../test/test_tinyshell.h" //
# include "../tinyshell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		msh_echo(int argc, char *argv[], char *env[]);
int		msh_pwd(int argc, char *argv[], char *env[]);
int		msh_cd(const int argc, const char *argv[], char **env[]);
int		msh_env(int argc, char *argv[], char *env[]);
int		msh_export(const int argc, const char *argv[], char **env[]);
int		msh_unset(const int argc, const char *argv[], char **env[]);
int		msh_exit(int argc, char *argv[], char *env[]);
int		is_valid_env_name(const char *env_ptr);
int		get_env_pos(const char *name, const char **env);
char	*get_env_var_value(const char *name, const char **env);
char	*get_cur_dir(void);
char	*get_home(const char **env);
void	change_pwd_oldpwd(char *oldpwd, char **env[]);
char	*get_cur_dir_s(const char *env[]);
void	print_not_valid(const char *var);
void	msh_export_print(const char **str_array);

#endif
