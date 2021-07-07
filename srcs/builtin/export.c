/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:33:23 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/07 21:24:32 by ngamora          ###   ########.fr       */
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
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

size_t	str_array_size(char **str_array)
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

	size = (int)str_array_size(str_array);
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

char	**str_array_copy(char **str_array)
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

void	msh_export_print(char **str_array)
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

int		msh_export(int argc, char *argv[], char *env[])
{
	char	**copy;

	if (argc == 1)
	{
		copy = str_array_copy(env);
		str_array_sort(copy);
		msh_export_print(copy);
		str_array_free(copy);
	}
	else
	{
		int	i = 1; //iteration
		int	j = 0;
		char	*name;
		char	*value;
		char	*equal;

		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd("\n", 1);

		if ((equal = ft_strnstr(argv[i], "=", ft_strlen(argv[i]))))
		{
			name = ft_substr(argv[i], 0, equal - argv[i]);
			if (name)
				return (1); //
			j = 0;
			while (name[j])
			{
				if (!ft_isalnum(name[j]) && name[j] != '_')
					perror("ERROR"); //
				j++;
			}

			free(name);
		}
	}
	return (0);
}

int		main(int argc, char *argv[], char *env[])
{
	msh_export(argc, argv, env);
	return (0);
}
