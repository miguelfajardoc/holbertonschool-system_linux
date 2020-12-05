#include "hls.h"

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
	errorBuffer = malloc(512);
	sprintf(errorBuffer, errorString, file_error);
	perror(errorBuffer);
	free(errorBuffer);
}
