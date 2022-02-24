#include "tinylibc.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < (int)(n - 1) && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
