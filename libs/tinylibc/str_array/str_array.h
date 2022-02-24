#ifndef STR_ARRAY_H
# define STR_ARRAY_H

# include "../tinylibc.h"
# include <stdlib.h>

char	**str_array_free(char **str_array[]);
size_t	str_array_size(const char *str_array[]);
char	**str_array_sort(char *str_array[]);
char	**str_array_copy(const char *str_array[]);
char	**str_array_add_back(char **str_array[], const char *str);
char	**str_array_erase(char **str_array[], int pos);

#endif
