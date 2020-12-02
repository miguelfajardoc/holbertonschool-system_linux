# include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	DIR *dir;
	char *directory;
	struct dirent *read;

	if (argc <= 1)
		directory = ".";
	else
		directory = argv[1];

	dir = opendir(directory);
	if (dir == NULL)
		return (0);
	read = readdir(dir);
	while(read != NULL)
	{
		printf("%s\n", read->d_name);
		read = readdir(dir);
	}

	closedir(dir);
	return (1);
}
