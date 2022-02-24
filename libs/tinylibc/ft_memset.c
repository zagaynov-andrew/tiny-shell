#include "tinylibc.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_b;

	ptr_b = (unsigned char *)b;
	while (len--)
		*ptr_b++ = (unsigned char)c;
	return (b);
}
