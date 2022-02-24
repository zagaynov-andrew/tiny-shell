#include "tinylibc.h"

int	ft_lli_len(long long int n)
{
	int	str_len;

	if (n == 0)
		return (1);
	str_len = 0;
	if (n < 0)
		str_len++;
	while (n)
	{
		str_len++;
		n /= 10;
	}
	return (str_len);
}
