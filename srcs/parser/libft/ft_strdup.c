/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:07:37 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 20:57:32 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*strdup;
	int		i;

	i = 0;
	strdup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (strdup && str)
	{
		while (*str)
		{
			*strdup++ = *str++;
			i++;
		}
		*strdup = '\0';
	}
	else
		return (NULL);
	return (strdup - i);
}
