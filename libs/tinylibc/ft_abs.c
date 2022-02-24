#include "tinylibc.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
