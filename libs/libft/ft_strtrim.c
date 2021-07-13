/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:25:12 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/27 12:58:19 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_char_in_set(const char *set, char c)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strtrim_size(char const *s1, char const *set,
							int *start, int *end)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (s1[i] && ft_char_in_set(set, s1[i]))
	{
		size++;
		i++;
	}
	*start = i;
	if (!s1[i])
	{
		*start = -1;
		return (ft_strlen(s1) - size);
	}
	i = ft_strlen(s1) - 1;
	while (i > -1 && ft_char_in_set(set, s1[i]))
	{
		size++;
		i--;
	}
	*end = i;
	return (ft_strlen(s1) - size);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char*)s1);
	ft_strtrim_size(s1, set, &start, &end);
	if (start == -1)
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, start, end - start + 1));
}
