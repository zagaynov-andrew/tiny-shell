/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:28:24 by ngamora           #+#    #+#             */
/*   Updated: 2020/11/20 16:24:05 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	needle_len;

	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	needle_len = ft_strlen(needle);
	while (i < (int)len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if ((int)len - i >= needle_len)
			{
				if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
					return ((char*)&haystack[i]);
			}
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
