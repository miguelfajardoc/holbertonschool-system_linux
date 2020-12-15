#include "_getline.h"

/**
 * _getline - Write a function that reads an entire line from a file descriptor
 * @fd: is the file descriptor to read from
 * Return: A pointer with the data readed (is static variable) or NULL in if
 * there are no more lines to return or in error.
 */

char *_getline(const int fd)
{
	static char *buf, *new_line;
	int result, new_line_pos;
	int reading = 1, in_buffer = 0, found = 0;
	char *aux_buff;

	while (reading)
	{
		if (buf == NULL || buf[0] == '\0' || in_buffer)
		{
			buf = malloc(sizeof(char) * (READ_SIZE));
			if (buf == NULL)
				return (NULL);
			memset(buf, '\0', READ_SIZE + 1);
			result = read(fd, buf + in_buffer,
				      READ_SIZE - 1 - in_buffer);
			if (result == 0 || result == -1)
			{
				free(buf), return (NULL);
			}
			if (in_buffer)
			{
				strncpy(buf, aux_buff, new_line_pos);
				free(aux_buff);
			}
		}
		new_line_pos = check_newline(buf, &found);
		if (!found)
		{
			aux_buff = malloc(sizeof(char) * new_line_pos);
			strcpy(aux_buff, buf), in_buffer = new_line_pos - 1;
		}
		else
			reading = 0;
	}
	new_line = malloc(sizeof(char) * (new_line_pos + 1));
	if (new_line == NULL)
		return (NULL);
	strncpy(new_line, buf, new_line_pos), new_line[new_line_pos] = '\0';
	buf += (new_line_pos + 1);
	return (new_line);
}

/**
 * check_newline - check the position of the new line character
 * @buffer: is the buffer to read from
 * @found: pointer to derreference if a new line char is found
 * Return: the position where the new line is found or 0 if not found
 */
int check_newline(char *buffer, int *found)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*found = 1;
			break;
		}
		i++;
	}
	return (i);
}
