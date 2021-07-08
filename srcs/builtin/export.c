/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:33:23 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/08 18:53:32 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


void	str_swap(char **str_1, char **str_2)
{
	char	*tmp;

	tmp = *str_1;
	*str_1 = *str_2;
	*str_2 = tmp;
}

void	str_array_free(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		// printf("%p\n", str_array[i]);
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

size_t	str_array_size(const char **str_array)
{
	size_t	size;

	size = 0;
	while (str_array[size])
		size++;
	return (size);
}

char	**str_array_sort(char **str_array)
{
	int	i;
	int	j;
	int	size;

	size = (int)str_array_size((const char **)str_array);
	j = 1;
	while (j < size)
	{
		i = 0;
		while (i < size - j)
		{
			if (ft_strcmp(str_array[i], str_array[i + 1]) > 0)
				str_swap(&str_array[i], &str_array[i + 1]);
			i++;
		}
		j++;
	}
	return (str_array);
}

char	**str_array_copy(const char **str_array)
{
	int		i;
	int		size;
	char	**copy;

	size = (int)str_array_size(str_array);
	copy = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(str_array[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	msh_export_print(const char **str_array)
{
	int	i;
	int	j;

	i = 0;
	while (str_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (str_array[i][j] != '=')
		{
			ft_putchar_fd(str_array[i][j], 1);
			j++;
		}
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(&str_array[i][j + 1], 1);
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

int		get_env_pos(const char *name, const char **env)
{
	int		i;
	int		cur_name_len;
	int		name_len;
	char	*equal;

	if ((equal = ft_strnstr(name, "=", ft_strlen(name))))
		name_len = equal - name;
	else
		name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((equal = ft_strnstr(env[i], "=", ft_strlen(env[i]))))
			cur_name_len = equal - env[i];
		else
			cur_name_len = ft_strlen(env[i]);
		if (name_len == cur_name_len
				&& ft_strncmp(env[i], name, cur_name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		is_correct_name(const char *env_ptr)
{
	int		name_len;
	char	*equal;
	int		i;

	if ((equal = ft_strnstr(env_ptr, "=", ft_strlen(env_ptr))))
		name_len = equal - env_ptr;
	else
		name_len = ft_strlen(env_ptr);
	i = 0;
	while (i < name_len)
	{
		if (!ft_isalnum(env_ptr[i]) && env_ptr[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	**str_array_add_back(const char **str_array, const char *str)
{
	char	**new;
	int		i;
	int		old_size;

	if (!str_array)
		return (NULL);
	old_size = str_array_size(str_array);
	if (!(new = ft_calloc(old_size + 2, sizeof(char*))))
	{
		str_array_free((char **)str_array);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new[i] = (char *)str_array[i];
		i++;
	}
	new[i] = (char *)str;
	new[i + 1] = NULL;
	str_array_free((char **)str_array);
	return (new);
}

int		msh_export(const int argc, const char *argv[], const char *env[])
{
	char	**copy;

	if (argc == 1)
	{
		if (!(copy = str_array_copy(env)))
			return (errno);
		str_array_sort(copy);
		msh_export_print((const char **)copy);
		str_array_free(copy);
	}
	else
	{
		int		i = 1; // iteration
		int		pos;

		if (!is_correct_name(argv[i]))
		{
			perror("ERROR"); //
			return (1); //
		}
		if ((pos = get_env_pos(argv[i], env)) >= 0)
		{
			if (!ft_strnstr(argv[i], "=", ft_strlen(argv[i])))
				return (0);
			free((char*)env[pos]);
			env[pos] = ft_strdup(argv[i]);
		}
		else
		{
			if (!(copy = str_array_add_back(env, argv[i])))
			{
				perror("ERROR"); //
				return (errno);
			}
		}
		printf("");
	}
	return (0);
}

int		main(const int argc, const char *argv[], const char *env[])
{
	char	**copy_env = str_array_copy(env);
	msh_export(argc, argv, (const char **)copy_env);
	print_str_array(copy_env);
	str_array_free(copy_env);
	return (0);
}
