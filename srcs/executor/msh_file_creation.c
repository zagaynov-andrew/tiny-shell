/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_file_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:04:19 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/11 18:07:43 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	create_files(char **cmd_array)
{
	int		fd;
	int		i;

	i = 0;
	while (cmd_array[i])
	{
		if (ft_strcmp(cmd_array[i], ">") == 0)
		{
			fd = open(cmd_array[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
			close(fd);
			if (fd < 0)
				return (1);
			i++;
		}
		else if (ft_strcmp(cmd_array[i], ">>") == 0)
		{
			fd = open(cmd_array[i + 1], O_CREAT | O_RDWR, 0644);
			close(fd);
			if (fd < 0)
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

int	msh_file_creation(t_list *shell_lst)
{
	while (shell_lst)
	{
		if (create_files((char **)(shell_lst->content)))
			return (1);
		shell_lst = shell_lst->next;
	}
	return (0);
}
