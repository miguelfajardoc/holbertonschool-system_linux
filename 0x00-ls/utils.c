#include "hls.h"

/**
 * check_for_data - this function check the argv looking for flags, files and
 * directories and save it in the corresponding pointer
 * @flags: pointer to save the flags founded
 * @files: pointer to pointers to point the file names to list
 * @directories: pointer to save the directories found
 * @argv: the pointer that points the input arguments
 * @argc: the amount of arguments of argv
 * @data_amount: pointer to save the amount of data found, in the first position
 * save the amount of flags, the second the amount of files, and the last the
 * directories.
 * Return: 1 on sucess, 0 on failure
 */
int check_for_data(char *flags, char **files, char **directories, char **argv,
		   int argc, int *data_amount)
{
	int p_iter, w_iter, error;
	int flags_iter = 0, files_iter = 0, directories_iter = 0;
	DIR *dir_test;

	for (p_iter = 1; p_iter < argc; p_iter++)
	{
		if (argv[p_iter][0] == '-')
		{
			for (w_iter = 1; argv[p_iter][w_iter] != '\0'; w_iter++)
			{
				flags[flags_iter] = argv[p_iter][w_iter];
				flags_iter++;
			}
		}
		else
		{
			dir_test = opendir(argv[p_iter]);
			error = errno;
			if (dir_test != NULL)
			{
				directories[directories_iter] = argv[p_iter];
				directories_iter++;
				closedir(dir_test);
			}
			else
			{
				if (error == ENOTDIR)
				{
					files[files_iter] = argv[p_iter];
					files_iter++;
				}
				else
					error_handler(error, argv[p_iter]);
			}
		}
	}
	if (directories_iter == 0)
	{
		directories[directories_iter] = ".";
		directories_iter++;
	}
	data_amount[0] = flags_iter;
	data_amount[1] = files_iter;
	data_amount[2] = directories_iter;
	return (1);
}



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
