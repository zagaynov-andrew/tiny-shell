#include "tinyshell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_list	*cmds;
	t_list	*redirs;
	char	**env_copy;
	t_list	*shell_lst;
	char	*msh_path;

	(void)argc;
	(void)argv;
	cmds = NULL;
	redirs = NULL;
	shell_lst = NULL;
	env_copy = str_array_copy((const char **)env);
	if (!env_copy)
		exit(msh_strerror(EXIT_FAILURE));
	inc_shell_lvl("tinyshell", &env_copy);
	msh_path = ft_strjoin("SHELL=", argv[0]);
	set_env_var(msh_path, &env_copy);
	free(msh_path);
	prompt_loop(&cmds, &redirs, &env_copy, &shell_lst);
	clear_shell_lst(&shell_lst, &cmds, &redirs, NULL);
	str_array_free(&env_copy);
	return (g_last_exit_status);
}

void	add_to_history(char *input)
{
	if (input)
		add_history(input);
}

void	set_env_var(char *env_str, char **env[])
{
	char	**argv;

	if (!env_str)
		return ;
	argv = NULL;
	str_array_add_back(&argv, "export");
	if (!argv)
		exit(msh_strerror(EXIT_FAILURE));
	str_array_add_back(&argv, env_str);
	if (!argv)
		exit(msh_strerror(EXIT_FAILURE));
	msh_export(2, (const char **)argv, env);
	str_array_free(&argv);
}
