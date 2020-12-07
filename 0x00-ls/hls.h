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
int check_for_files(char **files_position, char **argv, int argc);
int read_file(DIR *dir, char *dir_name, char *flags, int flags_amount);
int open_directories(char *flags, char **directories, int *data_amount);
void error_handler(int _errno, char *file_error);
int check_for_flags(char *flags, int argc, char **argv);
int printls(struct dirent *read, char *flags, int flags_amount,
	     struct stat buf);
int  printfiles(char *flags, char **files, int *data_amount);
int check_for_data(char *flags, char **files, char **directories, char **argv,
		   int argc, int *data_amount);

#endif /* HLS_HEADER */
