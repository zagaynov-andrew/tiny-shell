#include "tinylibc.h"

int	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return (0);
	return ((int)write(fd, s, ft_strlen(s)));
}
