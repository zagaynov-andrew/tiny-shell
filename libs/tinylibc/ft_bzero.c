#include "tinylibc.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = (unsigned char)0;
	return ;
}
