#include "tinylibc.h"

int	ft_putnstr_fd(char *s, size_t len, int fd)
{
	int	slen;
	int	total;

	total = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if ((int)len > slen)
	{
		total += (int)write(fd, s, ft_strlen(s));
		return (total);
	}
	else
	{
		total += (int)write(fd, s, len);
		return (total);
	}
}
