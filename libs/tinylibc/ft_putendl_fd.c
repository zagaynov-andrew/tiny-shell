#include "tinylibc.h"

int	ft_putendl_fd(char *s, int fd)
{
	const char	endl = '\n';
	int			total;

	total = 0;
	if (!s)
		return (write(fd, &endl, 1));
	total += (int)write(fd, s, ft_strlen(s));
	total += (int)write(fd, &endl, 1);
	return (total);
}
