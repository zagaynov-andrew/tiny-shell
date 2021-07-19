/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:42:45 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/15 18:29:56 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + s2_len + 1);
	ft_strlcpy(&newstr[s1_len], s2, s2_len + 1);
	return (newstr);
}
