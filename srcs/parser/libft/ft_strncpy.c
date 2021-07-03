void	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && n)
	{
		dst[i] = src[i];
		n--;
		i++;
	}
	dst[i] = '\0';
}
