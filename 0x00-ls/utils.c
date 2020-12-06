#include "hls.h"

/**
 * check_for_files - This function check in the argv where in the argv are
 * the name of the directories or files to list
 * @files_names: pointer to pointers to point the file names to list
 * @argv: the pointer that points the input arguments
 * @argc: the amount of arguments of argv
 * Return: the number of files or directories to list
 */
int check_for_files(char **files_names, char **argv, int argc)
{
	int iter;
	int number = 0;

	for (iter = 1; iter < argc; iter++)
	{
		if (argv[iter][0] != '-')
		{
			files_names[number] = argv[iter];
			number++;
		}
	}
	if (number == 0)
	{
		files_names[0] = ".";
		number++;
	}
	return (number);
}

/**
 * error_handler - this function receive an errno and prepare a string to
 * return an apropiate perror
 * @_errno: the errno generated
 * @file_error: file that generate the error
 */
void error_handler(int _errno, char *file_error)
{
	char *errorBuffer;
	char *accessError;
	char *permissionError;
	char *errorString;

	accessError = "hls: cannot access %s";
	permissionError = "hls: cannot open directory %s";

	if (_errno == EACCES)
		errorString = permissionError;
	else
		errorString = accessError;
	errorBuffer = malloc(512);
	sprintf(errorBuffer, errorString, file_error);
	perror(errorBuffer);
	free(errorBuffer);
}

/**
 * check_for_flags - This function check for flags in the argv and saveit
 * @flags: pointer to an array of strings with the flags
 * @argv: the pointer that points the input arguments
 * @argc: the amount of arguments of argv
 * Return: the number of flags found
 */
int check_for_flags(char *flags, int argc, char **argv)
{
	int p_iter;
	int w_iter;
	int f_iter;

	f_iter = 0;
	for (p_iter = 0; p_iter < argc; p_iter++)
	{
		if (argv[p_iter][0] == '-')
		{
			for (w_iter = 1; argv[p_iter][w_iter] != '\0'; w_iter++)
			{
				flags[f_iter] = argv[p_iter][w_iter];
				f_iter++;
			}
		}
	}
	return (f_iter);
}
