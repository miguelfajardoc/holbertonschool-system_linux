#include "_getline.h"

/**
 * _getline - Write a function that reads an entire line from a file descriptor
 * @fd: is the file descriptor to read from
 * Return: A pointer with the data readed (is static variable) or NULL in if
 * there are no more lines to return or in error.
 */
char *_getline(const int fd)
{
	static char *buf;
	int result;

	buf = malloc(sizeof(char) * (READ_SIZE));
	memset(buf, '\0', READ_SIZE);
	result = read(fd, buf, READ_SIZE - 1);
	printf("result: %d\n", result);
	if (result == 0 || result == -1)
	{
		free(buf);
		return NULL;
	}
	return buf;
}
