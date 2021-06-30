/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_file_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:04:19 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/30 16:48:15 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	create_files(void *redirs)
{
	char	**path;
	int		fd;

	path = (char **)redirs;
	if (ft_strcmp(path[1], "") != 0)
	{
		printf("%s\n", path[1]);
		fd = open(path[1], O_TRUNC | O_CREAT | O_RDWR);
		close(fd);
	}
	if (ft_strcmp(path[2], "") != 0)
	{
		printf("%s\n", path[2]);
		fd = open(path[2], O_CREAT | O_RDWR);
		close(fd);
	}
}

void	msh_file_creation(t_list *redirs)
{
	ft_lstiter(redirs, create_files);
}
