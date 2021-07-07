/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/06 23:06:21 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "test/test_minishell.h"
#include <signal.h>

int	main(int argc, char *argv[], char *env[])
{
	// msh_loop(env);
	t_list *cmds = NULL;
	t_vec	*vec;

	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("cd"));
	// ft_vec_push(&vec, (void*)ft_strdup("-n"));
	// ft_vec_push(&vec, (void*)ft_strdup("hello"));
	// ft_vec_push(&vec, (void*)ft_strdup("world"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
	free(vec);

	// vec = ft_vec_new(4);
	// ft_vec_push(&vec, (void*)ft_strdup("head"));
	// ft_vec_push(&vec, (void*)ft_strdup("-n"));
	// ft_vec_push(&vec, (void*)ft_strdup("3"));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&cmds, ft_lstnew(vec->data));
	// free(vec);

	vec = ft_vec_new(3);
	ft_vec_push(&vec, (void*)ft_strdup("grep"));
	ft_vec_push(&vec, (void*)ft_strdup("PWD"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
	free(vec);

	print_list_str_array(cmds);

	t_list *redirs = NULL;

	vec = ft_vec_new(4);
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&redirs, ft_lstnew(vec->data));
	free(vec);

	vec = ft_vec_new(4);
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, (void*)ft_strdup(""));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&redirs, ft_lstnew(vec->data));
	free(vec);

	// vec = ft_vec_new(4);
	// ft_vec_push(&vec, (void*)ft_strdup("/Users/ngamora/minishell/file2"));
	// ft_vec_push(&vec, (void*)ft_strdup(""));
	// ft_vec_push(&vec, (void*)ft_strdup(""));
	// ft_vec_push(&vec, NULL);
	// ft_lstadd_back(&redirs, ft_lstnew(vec->data));
	// free(vec);

	print_list_str_array(redirs);
	msh_file_creation(redirs);
	msh_exec(cmds, redirs, env);


	ft_lstclear(&cmds, str_array_free);
	ft_lstclear(&redirs, str_array_free);
	return (0);
}

