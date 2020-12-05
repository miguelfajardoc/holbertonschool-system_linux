#ifndef HLS_HEADER
#define HLS_HEADER

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int _strncmp(char *s1, char *s2, int n);
void check_for_files(int *files_position, char **argv, int argc);
int read_file(DIR *dir, char *dir_name);
int open_directories(int argc, char **argv, int *files_position);
void error_handler(int _errno, char *file_error);

#endif /* HLS_HEADER */
