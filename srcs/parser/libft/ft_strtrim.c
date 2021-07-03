/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:30:40 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:05:04 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnew(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str)
	{
		while (n--)
			str[i++] = '\0';
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

static int	ft_findex(const char *s1, const char *set)
{
	size_t	start;

	start = 0;
	while (ft_strchr(set, *s1) && *s1)
	{
		s1++;
		start++;
	}
	return (start);
}

static int	ft_bindex(const char *set, const char *tmp, int len)
{
	while (ft_strchr(set, *tmp) && len)
	{
		tmp--;
		len--;
	}
	return (len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	end;
	size_t	start;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	start = ft_findex(s1, set);
	if (start == ft_strlen(s1))
		return (ft_strnew(1));
	end = ft_bindex(set, s1 + ft_strlen(s1), ft_strlen(s1));
	if (end >= start)
	{
		strtrim = (char *)malloc(sizeof(char) * (end - start + 1));
		if (strtrim)
		{
			while (start < end)
				strtrim[i++] = s1[start++];
			strtrim[i] = '\0';
			return (strtrim);
		}
	}
	return (NULL);
}
