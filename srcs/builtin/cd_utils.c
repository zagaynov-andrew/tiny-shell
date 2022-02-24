/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:21:03 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/21 16:28:09 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	set_oldpwd(char *oldpwd, char **env[])
{
	char	*new;
	char	**args;

	new = ft_strjoin("OLDPWD=", oldpwd);
	if (!new)
		exit(msh_strerror(EXIT_FAILURE));
	args = NULL;
	str_array_add_back(&args, "export");
	if (!args)
		exit(msh_strerror(EXIT_FAILURE));
	str_array_add_back(&args, new);
	free(new);
	if (!args)
		exit(msh_strerror(EXIT_FAILURE));
	msh_export(2, (const char **)args, env);
	str_array_free(&args);
}

static void	set_pwd(const char **env[])
{
	char	*pwd;
	char	*new;
	char	**args;

	pwd = get_cur_dir_s((const char **)*env);
	if (!pwd)
		exit(msh_strerror(EXIT_FAILURE));
	new = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!new)
		exit(msh_strerror(EXIT_FAILURE));
	args = NULL;
	str_array_add_back(&args, "export");
	if (!args)
		exit(msh_strerror(EXIT_FAILURE));
	str_array_add_back(&args, new);
	free(new);
	if (!args)
		exit(msh_strerror(EXIT_FAILURE));
	msh_export(2, (const char **)args, (char ***)env);
	str_array_free(&args);
}

void	change_pwd_oldpwd(char *oldpwd, char **env[])
{
	set_oldpwd(oldpwd, env);
	set_pwd((const char ***)env);
}

char	*get_home(const char **env)
{
	char	*home;

	home = get_env_var_value("HOME", env);
	if (!ft_strcmp(home, ""))
	{
		free(home);
		home = getenv("HOME");
	}
	return (home);
}

char	*get_cur_dir_s(const char *env[])
{
	char	*pwd;

	pwd = get_cur_dir();
	if (pwd && ft_strcmp(pwd, ""))
		return (pwd);
	if (!ft_strcmp(pwd, ""))
		free(pwd);
	pwd = get_env_var_value("PWD", env);
	return (pwd);
}
