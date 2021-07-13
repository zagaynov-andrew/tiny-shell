/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:32:28 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/17 22:07:37 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c, int i)
{
	int	word_len;

	word_len = 0;
	while (s[i] && s[i] != c)
	{
		word_len++;
		i++;
	}
	return (word_len);
}

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	**ft_fill_split(char const *s, char c, char **split)
{
	int	i;
	int	row;
	int	word_len;

	i = 0;
	row = 0;
	while (s[i])
		if (s[i] != c)
		{
			word_len = ft_word_len(s, c, i);
			split[row] = ft_substr(s, i, word_len);
			if (!split[row])
			{
				ft_free_split(split);
				return (NULL);
			}
			i += word_len;
			row++;
		}
		else
			i++;
	split[row] = NULL;
	return (split);
}

char		**ft_split(char const *s, char c)
{
	char	**split;
	int		qty_words;

	if (!s)
		return (NULL);
	qty_words = ft_count_words(s, c);
	if (!(split = ft_calloc(qty_words + 1, sizeof(char*))))
		return (NULL);
	ft_fill_split(s, c, split);
	return (split);
}
