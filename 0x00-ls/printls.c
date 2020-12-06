#include "hls.h"

/**
 * printls - the printls formatter
 * @read: the data of the file to print
 * @flags: the pointer of the flags
 * @flags_amount: the cuatity of flags
 * @buf: the buffer with the data of the file
 * Return: 1 on one activated, 0 otherwise
 */
int  printls(struct dirent *read, char *flags,
	     int flags_amount, struct stat buf)
{
	int i;
	int all = 0;
	int one = 0;

	buf = buf;
	if (flags != NULL)
	{
		for (i = 0; i < flags_amount; i++)
		{
			if (flags[i] == '1')
				one = 1;
			if (flags[i] == 'a')
				all = 1;
		}
	}
	if (all)
	{
		printf("%s", read->d_name);
		if (one)
			printf("\n");
		else
			printf(" ");
	}
	else if (_strncmp(read->d_name, ".", 1) && _strncmp(read->d_name, "..",
							    2))
	{
		printf("%s", read->d_name);
		if (one)
			printf("\n");
		else
			printf(" ");
	}

	return (one);
}
