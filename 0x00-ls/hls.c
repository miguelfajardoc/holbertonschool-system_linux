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
		/* printf("%s with '.' : %d\n", read->d_name, */
		/* _strncmp(read->d_name, ".", 1)); */
		/* printf("%s with '..' : %d\n", read->d_name, */
		/* _strncmp(read->d_name, "..", 2)); */
		if (_strncmp(read->d_name, ".", 1) &&
		    _strncmp(read->d_name, "..", 2))
		{
			printf("%s", read->d_name);
			if (read != NULL)
				printf(" ");
		}
		read = readdir(dir);
	}
	printf("\n");
	closedir(dir);
	return (1);
}

/**
 * _strncmp - This is like strncmp
 * @s1: the pointer that points first string
 * @s2: the pointer that points second string
 * @n: the number of letters to compare
 * Return: 0 if there equal
 */
int _strncmp(char *s1, char *s2, int n)
{
	int iter;
	int validator = 0;

	for (iter = 0; iter < n; iter++)
	{
		/* printf("in strcmp %c and %c with iter: %d son %d\n",*/
		/* s1[iter], s2[iter], iter, s1[iter] != s2[iter]); */
		if (s1[iter] != s2[iter])
		{
			/* printf("entre\n"); */
			validator = iter + 1;
			break;
		}
	}
	return (validator);
}
