/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:04:47 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/18 15:57:02 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*msh_heredoc_utils(char *heredoc, char *input)
{
	char	*tmp;

	tmp = heredoc;
	heredoc = ft_strjoin(heredoc, input);
	free(tmp);
	free(input);
	if (!heredoc)
		exit(msh_strerror(EXIT_FAILURE));
	tmp = heredoc;
	heredoc = ft_strjoin(heredoc, "\n");
	free(tmp);
	if (!heredoc)
		exit(msh_strerror(EXIT_FAILURE));
	return (heredoc);
}

static char	*checkinging_input(char *heredoc, char *delimeter)
{
	char	*input;

	while (1)
	{
		init_signals(sig_catcher_heredoc);
		input = readline("\033m> \033[0m");
		if (g_last_exit_status)
		{
			free(input);
			free(heredoc);
			if (g_last_exit_status)
				return (NULL);
		}
		if (!input)
			break ;
		if (ft_strcmp(input, delimeter) == 0)
		{
			free(input);
			break ;
		}
		heredoc = msh_heredoc_utils(heredoc, input);
	}
	return (heredoc);
}

char	*msh_heredoc(char *delimeter)
{
	char	*heredoc;

	heredoc = ft_strdup("");
	if (!heredoc || !delimeter)
		exit(msh_strerror(EXIT_FAILURE));
	heredoc = checkinging_input(heredoc, delimeter);
	if (!heredoc)
		return (NULL);
	if (ft_strcmp(heredoc, "") == 0)
	{
		free(heredoc);
		heredoc = NULL;
	}
	return (heredoc);
}
