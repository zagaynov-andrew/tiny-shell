/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:13:23 by ngamora           #+#    #+#             */
/*   Updated: 2021/07/09 23:30:02 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_ARRAY_H
# define STR_ARRAY_H

# include "../libft.h"
# include <stdlib.h>

void	str_array_free(char **str_array);
size_t	str_array_size(const char **str_array);
char	**str_array_sort(char **str_array);
char	**str_array_copy(const char **str_array);
char	**str_array_add_back(char **str_array, const char *str);

#endif