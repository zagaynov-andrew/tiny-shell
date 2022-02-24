#include "tinylibc.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	*dst_uc;
	unsigned char	*src_uc;

	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	i = 0;
	while (i < (int)n)
	{
		dst_uc[i] = src_uc[i];
		if (src_uc[i] == (unsigned char)c)
			return (dst_uc + i + 1);
		i++;
	}
	return (NULL);
}
