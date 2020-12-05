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
	int files_position[50];
	int result;

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
	{
		check_for_files(files_position, argv, argc);
		result = open_directories(argc, argv, files_position);
	}
	return (result);
}
/**
 * open_directories - this function open the directories to read from the argv
 * and the files_position.
 * @argv: the pointer that points the input arguments
 * @argc: the amount of arguments of argv
 * @files_position: pointer to an array of integers to fill where a directory
 * or file name is found
 * Return: 1 on sucess, 0 otherwise
 */
int open_directories(int argc, char **argv, int *files_position)
{
	DIR *dir;
	int files_i;
	char *directory;
	int error;

	for (files_i = 1; files_i < argc; files_i++)
	{
		if (files_position[files_i] != 0)
		{
			directory = argv[files_i];
			dir = opendir(directory);
			error = errno;
			if (dir == NULL)
			{
				if (error == ENOTDIR)
					printf("%s\n", directory);
				else
				{
					error_handler(error, directory);
				}
			}
			else
			{
				if (argc > 2)
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
	char *buffer, *errorBuffer;
	char *full_name = dir_name;

	buffer = malloc(512);
	if (buffer == NULL)
		return (0);
	read = readdir(dir);
	while (read != NULL)
	{
		if (dir_name[0] != '.')
		{
			sprintf(buffer, "./%s/%s", dir_name, read->d_name);
			full_name = buffer;
		}
		stat_response = lstat(full_name, &buf);
		if (stat_response != 0)
		{
			errorBuffer = malloc(512);
			sprintf(errorBuffer, "hls: cannot access %s",
				buffer);
			perror(errorBuffer);
			free(errorBuffer), free(buffer);
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

