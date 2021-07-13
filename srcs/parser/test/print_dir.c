#include "parser.h"

int main() 
{
    DIR				*dir;
    struct dirent	*entry;

	dir = opendir("~/.dotnet/tools");
	if (!dir) 
	{
        perror("diropen");
        exit(1);
    }
	entry = readdir(dir);
	while (entry  != NULL)
	{
        printf("%s\n",
            entry->d_name);
		entry = readdir(dir);
	}
    closedir(dir);
};