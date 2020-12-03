#include "hls.h"

/**
 * main - This is like ls
 * @argc: the size of the arguments input
 * @argv: the pointer of the arguments
 * Return: 1 on suces, -1 otherwise
 */

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
	while (read != NULL)
	{
		stat_response = lstat(read->d_name, &buf);
		if (stat_response != 0)
			fprintf(stderr, "error in lstat: %s\n", strerror(errno));
		printf("%s", read->d_name);
		read = readdir(dir);
		if (read != NULL)
			printf(" ");
	}
	printf("\n");

	closedir(dir);
	return (1);
}
