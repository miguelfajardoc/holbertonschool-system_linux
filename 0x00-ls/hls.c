#include "hls.h"

/**
 * main - This is like ls
 * @argc: the size of the arguments input
 * @argv: the pointer of the arguments
 * Return: 1 on suces, -1 otherwise
 */
int main(int argc, char **argv)
{
	char *flags;
	char **files;
	char **directories;
	int data_amount[3];
	int result;

	files = malloc(sizeof(char **) * argc);
	flags = malloc(sizeof(char *) * argc);
	directories = malloc(sizeof(char **) * argc);

	check_for_data(flags, files, directories, argv, argc, data_amount);
	if (data_amount[1] > 0)
		printfiles(flags, files, data_amount);
	/* flags_amount = check_for_flags(flags, argc, argv); */
	/* files_amount = check_for_files(files, argv, argc); */
	result = open_directories(flags, directories, data_amount);

	free(files);
	free(flags);
	free(directories);
	return (result);
}

/**
 * open_directories - this function open the directories to read from the argv
 * and the files_position.
 * @flags: the pointer that points to the flags
 * @directories: the pointer that points to the files or directories
 * @data_amount: the amount of directories or files to list
 * Return: 1 on sucess, 0 otherwise
 */
int open_directories(char *flags, char **directories, int *data_amount)
{
	DIR *dir;
	int iter;
	char *directory;
	int error;

	for (iter = 0; iter < data_amount[2]; iter++)
	{
		directory = directories[iter];
		dir = opendir(directory);
		error = errno;
		if (dir == NULL)
		{
			error_handler(error, directory);
		}
		else
		{
			if (data_amount[2] > 1 || data_amount[1] > 0)
			{
				printf("%s:\n", directory);
			}
			read_file(dir, directory, flags, data_amount[0]);
		}
		closedir(dir);
		if (iter + 1 < data_amount[2])
			printf("\n");
	}
	return (1);
}

/**
 * read_file  - This function read the directory and print the files according
 * to sended flags, if any
 * @dir: the DIR pointer that contains the stream of de directory
 * @dir_name: the name of the directory
 * @flags: the flags to format the data of the ls
 * @flags_amount: the amount of flags founded as argumments
 * Return: 1 on succes, other if any error found
 */
int read_file(DIR *dir, char *dir_name, char *flags, int flags_amount)
{
	struct stat buf;
	int stat_response;
	struct dirent *read;
	char *buffer;
	char *full_name = dir_name;
	int error;
	int new_line = 0;

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
		error = errno;
		if (stat_response != 0)
		{
			error_handler(error, buffer);
			free(buffer);
			return (0);
		}
		new_line = printls(read, flags, flags_amount, buf);
		read = readdir(dir);
	}
	if (!new_line)
		printf("\n");
	free(buffer);
	return (1);
}
