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
	int files_position[argc];
	int files_i;

	if (argc <= 1)
	{
		directory = ".";
		dir = opendir(directory);
		if (dir == NULL)
		{
			return (0);
		}
		read_file(dir, directory);
		closedir(dir);
	}
	else
		check_for_files(files_position, argv, argc);
	for (files_i = 1; files_i < argc; files_i++)
	{
		if (files_position[files_i] != 0)
		{
			directory = argv[files_i];
			dir = opendir(directory);
			if (dir == NULL)
			{
				fprintf(stderr, "hls: cannot access %s: %s\n",
					directory, strerror(errno));
			}
			else
			{
				printf("%s:\n", directory);
				read_file(dir, directory);
			}
			closedir(dir);
		}
		if (files_i + 1 < argc)
			printf("\n");
	}
	return (1);
}

/**
 * check_for_files - This function check in the argv where in the argv are
 * the name of the directories or files to list
 * @files_position: pointer to an array of integers to fill where a directory
 * or file name is found
 * @argv: the pointer that points the input arguments
 * @argc: the amount of arguments of argv
 */
void check_for_files(int *files_position, char **argv, int argc)
{
	int iter;

	for (iter = 1; iter < argc; iter++)
	{
		if (argv[iter][0] != '-')
			files_position[iter] = 1;
		else
			files_position[iter] = 0;
	}
}

/**
 * read_file  - This function read the directory and print the files according
 * to sended flags, if any
 * @dir: the DIR pointer that contains the stream of de directory
 * @dir_name: the name of the directory
 * Return: 1 on succes, other if any error found
 */
int read_file(DIR *dir, char *dir_name)
{
	struct stat buf;
	int stat_response;
	struct dirent *read;

	char *restrict buffer = malloc(512);
	char *full_name = dir_name;

	read = readdir(dir);
	while (read != NULL)
	{
		if (dir_name[0] != '.')
		{
			sprintf(buffer, "./%s%s", dir_name, read->d_name);
			full_name = buffer;
			/* printf("reading: %s\n", buffer); */
		}
			/* printf("reading: %s\n", dir_name); */
		stat_response = lstat(full_name, &buf);
		if (stat_response != 0)
		{
			fprintf(stderr, "hls: cannot access %s: %s\n", full_name,
				strerror(errno));
			free(buffer);
			return (0);
		}
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
	free(buffer);
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
