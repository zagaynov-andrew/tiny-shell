/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:09:17 by skharjo           #+#    #+#             */
/*   Updated: 2021/04/17 21:13:52 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	strjoin = (char *)malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (strjoin)
	{
		while (*s1)
		{
			strjoin[i] = *s1++;
			i++;
		}
		while (*s2)
		{
			strjoin[i] = *s2++;
			i++;
		}
		strjoin[i] = '\0';
		return (strjoin);
	}
	return (NULL);
}
