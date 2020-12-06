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
	int flags_amount = 0;
	int files_amount = 0;
	int result;

	files = malloc(sizeof(char **) * argc);
	flags = malloc(sizeof(char *) * argc);

	flags_amount = check_for_flags(flags, argc, argv);
	files_amount = check_for_files(files, argv, argc);
	result = open_directories(flags, files, flags_amount, files_amount);

	free(files);
	free(flags);
	return (result);
}

/**
 * open_directories - this function open the directories to read from the argv
 * and the files_position.
 * @flags: the pointer that points to the flags
 * @files: the pointer that points to the files or directories
 * @flags_amount: the amount of flags
 * @files_amount: the amount of directories or files to list
 * Return: 1 on sucess, 0 otherwise
 */
int open_directories(char *flags, char **files, int flags_amount,
		     int files_amount)
{
	DIR *dir;
	int files_i;
	char *directory;
	int error;

	for (files_i = 0; files_i < files_amount; files_i++)
	{
		directory = files[files_i];
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
			if (files_amount > 1)
				printf("%s:\n", directory);
			read_file(dir, directory, flags, flags_amount);
		}
		closedir(dir);
		if (files_i + 1 < files_amount)
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
		printls(read, flags, flags_amount, buf);
		read = readdir(dir);
	}
	printf("\n");
	free(buffer);
	return (1);
}
