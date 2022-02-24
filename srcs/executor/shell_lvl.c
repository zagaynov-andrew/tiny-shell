/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:34:14 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/21 19:36:23 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	set_shell_lvl(int value, char **env[])
{
	char	**argv;
	char	*env_str;
	char	*value_str;

	value_str = ft_itoa(value);
	if (!value_str)
		exit(msh_strerror(EXIT_FAILURE));
	env_str = ft_strjoin("SHLVL=", value_str);
	free(value_str);
	if (!env_str)
		exit(msh_strerror(EXIT_FAILURE));
	argv = NULL;
	str_array_add_back(&argv, "export");
	if (!argv)
		exit(msh_strerror(EXIT_FAILURE));
	str_array_add_back(&argv, env_str);
	free(env_str);
	if (!argv)
		exit(msh_strerror(EXIT_FAILURE));
	msh_export(2, (const char **)argv, env);
	str_array_free(&argv);
}

static int	is_minishell(char *path)
{
	if (!ft_strcmp(path + ft_strlen(path) - ft_strlen("minishell"),
			"minishell"))
		return (1);
	return (0);
}

void	inc_shell_lvl(char *path, char **env[])
{
	char	*shell_lvl_value;
	int		shell_lvl_pos;

	if (!is_minishell(path))
		return ;
	shell_lvl_pos = get_env_pos("SHLVL", (const char **)*env);
	if (shell_lvl_pos == -1)
		set_env_var("SHLVL=1", env);
	else
	{
		shell_lvl_value = get_env_var_value("SHLVL", (const char **)*env);
		set_shell_lvl(ft_atoi(shell_lvl_value) + 1, env);
		free(shell_lvl_value);
	}
}
