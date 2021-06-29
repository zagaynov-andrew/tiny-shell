#include "executor.h"

void    str_array_free(void *str_array)
{
    int     i;
    char    **tmp;

    if (!str_array)
        return ;
    i = 0;
    tmp = (char **)str_array;
    while (tmp[i])
    {
        free(tmp[i]);
        i++;
    }
    free(str_array);
}