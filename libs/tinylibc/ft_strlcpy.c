#include "tinylibc.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	src_len;
	int	i;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < src_len && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
