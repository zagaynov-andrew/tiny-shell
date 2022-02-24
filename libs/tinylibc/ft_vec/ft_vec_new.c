#include "../ft_vec.h"

t_vec	*ft_vec_new(size_t capacity)
{
	t_vec	*vec;

	if (!capacity)
		return (NULL);
	vec = ft_calloc(capacity, sizeof(t_vec));
	if (!vec)
	{
		errno = ENOMEM;
		return (NULL);
	}
	vec->data = ft_calloc(capacity, sizeof(void *));
	if (!vec->data)
	{
		errno = ENOMEM;
		return (NULL);
	}
	vec->size = 0;
	vec->capacity = capacity;
	return (vec);
}
