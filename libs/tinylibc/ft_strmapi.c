#include "tinylibc.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*newstr;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	newstr = ft_calloc(sizeof(char), s_len + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	return (newstr);
}
