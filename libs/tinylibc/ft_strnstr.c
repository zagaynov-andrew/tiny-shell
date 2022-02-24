#include "tinylibc.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	needle_len;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	needle_len = ft_strlen(needle);
	while (i < (int)len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if ((int)len - i >= needle_len)
			{
				if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
					return ((char *)&haystack[i]);
			}
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
