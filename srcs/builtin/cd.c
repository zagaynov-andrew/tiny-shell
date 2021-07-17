/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:10:41 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/14 18:59:48 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_perror(char *str, int ret)
{
	if (!str)
		return (ret);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (ret);
}

static int	msh_cd_utils(char *oldpwd, int oldpwd_pos, int pwd_pos, char *env[])
{
	char	*pwd;

	pwd = get_cur_dir();
	if (!oldpwd || !pwd)
		return (1);
	if (oldpwd_pos != -1)
	{
		free(env[oldpwd_pos]);
		env[oldpwd_pos] = ft_strjoin("OLDPWD=", oldpwd);
		free(oldpwd);
		if (!env[oldpwd_pos])
			return (1);
	}
	if (pwd_pos != -1)
	{
		free(env[pwd_pos]);
		env[pwd_pos] = ft_strjoin("PWD=", pwd);;
		free(pwd);
		if (!env[pwd_pos])
			return (1);
	}
	return (0);
}

int	msh_cd(const int argc, const char *argv[], char **env[])
{
	int		pwd_pos;
	int		oldpwd_pos;
	char	*oldpwd;

	pwd_pos = get_env_pos("PWD", (const char **)*env);
	oldpwd_pos = get_env_pos("OLDPWD", (const char **)*env);
	oldpwd = get_cur_dir();
	if (argc == 1)
	{
		if (chdir(getenv("HOME")) != 0)
			return (cd_perror("HOME not set", EXIT_FAILURE));
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			errno = 0;
			return (EXIT_FAILURE);
		}
	}
	return (msh_cd_utils(oldpwd, oldpwd_pos, pwd_pos, *env));
}

// int main(int argc, char *argv[], char *env[])
// {
// 	char	**copy_env;



// 	copy_env = NULL;
// 	copy_env = str_array_copy((const char **)env);
// 	// str_array_ffree(copy_env);
// 	// copy_env = str_array_add_back(&copy_env, "pwd=string");
// 	// copy_env = str_array_add_back(&copy_env, "second=string");
// 	// copy_env = str_array_add_back(&copy_env, "OLDPWD=string");
// 	// copy_env = str_array_add_back(&copy_env, "PWD=string");
// 	// copy_env = str_array_add_back(&copy_env, "third=string");
// 	// copy_env = str_array_add_back(&copy_env, "forth=string");
//     msh_cd((const int)argc, (const char **)argv, &copy_env);
// 	char	*cur_dir = get_cur_dir();
// 	printf("PWD = %s\n", cur_dir);
// 	int	oldpwd_pos = get_env_pos("OLDPWD", (const char **)copy_env);
// 	int	pwd_pos = get_env_pos("PWD", (const char **)copy_env);
// 	printf("%s\n", copy_env[oldpwd_pos]);
// 	printf("%s\n", copy_env[pwd_pos]);
// 	free(cur_dir);
// 	str_array_free(copy_env);
//     return (0);
// }
