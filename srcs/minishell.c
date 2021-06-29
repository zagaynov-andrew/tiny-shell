/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:18:38 by ngamora           #+#    #+#             */
/*   Updated: 2021/06/29 21:54:20 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "test/test_minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	// msh_loop(env);
	t_list *cmds = NULL;
	t_vec	*vec;
	
	vec = ft_vec_new(2);
	ft_vec_push(&vec, (void*)ft_strdup("ls"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
	free(vec);

	vec = ft_vec_new(4);
	ft_vec_push(&vec, (void*)ft_strdup("cat"));
	ft_vec_push(&vec, (void*)ft_strdup("-e"));
	ft_vec_push(&vec, (void*)ft_strdup("-b"));
	ft_vec_push(&vec, NULL);
	ft_lstadd_back(&cmds, ft_lstnew(vec->data));
	free(vec);
	
	print_list_str_array(cmds);


	
	
	msh_exec(NULL, NULL, cmds);
	

	ft_lstclear(&cmds, str_array_free);
	return (0);
}

