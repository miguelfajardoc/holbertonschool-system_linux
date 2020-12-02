#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
	DIR *dir;
	char *directory;
	struct dirent *read;
	struct stat buf;
	int stat_response;

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
		stat_response = lstat(read->d_name, &buf);
		if (stat_response != 0)
			fprintf(stderr, "error in lstat: %s\n", strerror(errno));
		printf("%s %d\n", read->d_name, (int)(buf.st_size));
		read = readdir(dir);
	}

	closedir(dir);
	return (1);
}
