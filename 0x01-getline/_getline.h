#ifndef _GETLINE
#define _GETLINE

#define READ_SIZE 50

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *_getline(const int fd);
int check_newline(char *buffer, int *found);

#endif /*_GETLINE*/
