#include "tinylibc.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		s1_len;

	s1_len = ft_strlen(s1);
	s2 = (char *)malloc(s1_len + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, s1_len + 1);
	return (s2);
}
