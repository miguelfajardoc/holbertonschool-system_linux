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

void print_all(struct stat buf, char *name);
int get_permisions(mode_t mode, char *buffer);

int main(int argc, char **argv)
{
	DIR *dir;
	char *directory;
	struct dirent *read;
	struct stat buf;
	int stat_response;

	if (argc <= 1)
		directory = ".";
	else
		directory = argv[1];

	dir = opendir(directory);
	if (dir == NULL)
		return (0);
	read = readdir(dir);
	while(read != NULL)
	{
		stat_response = lstat(read->d_name, &buf);
		if (stat_response != 0)
			fprintf(stderr, "error in lstat: %s\n", strerror(errno));
		/* printf("%s %d\n", read->d_name, (int)(buf.st_size)); */
		print_all(buf, read->d_name);
		read = readdir(dir);
	}

	closedir(dir);
	return (1);
}



void print_all(struct stat buf, char *name)
{
	char type;
	char permisions[10];
	int size = buf.st_size;
	char *date = ctime(&buf.st_mtime);
	char formated_date[13];
	struct passwd *usr = getpwuid(buf.st_uid);
	struct group *grp = getgrgid(buf.st_gid);

	switch (buf.st_mode & S_IFMT)
	{
	case S_IFBLK:
		type = 'b';
		break;
	case S_IFCHR:
		type = 'c';
		break;
	case S_IFDIR:
		type = 'd';
		break;
	case S_IFIFO:
		type = 'p';
		break;
	case S_IFLNK:
		type = 'l';
		break;
	case S_IFREG:
		type = '-';
		break;
	case S_IFSOCK:
		type = 's';
		break;
	default:
		type = '?';
                break;
	}
	get_permisions(buf.st_mode, permisions);
	strncpy(formated_date, date + 4, 12);
	/* printf("name: %s\n", name); */
	/* printf("inodes: %ld\n", buf.st_ino); */
	/* printf("size: %d\n", (int)(buf.st_size)); */
	/* printf("mode: %d\n", (int)(buf.st_mode)); */
	/* printf("Permisions: %s\n", permisions); */
	/* printf("AllPermisions: %d\n", buf.st_mode & S_IWUSR); */
	/* printf("time: %s", ctime(&buf.st_mtime)); */
	/* printf("owner: %d\n", (buf.st_uid)); */
	/* printf("owner group: %d\n", (buf.st_gid)); */
	/* printf("type file %c\n\n", type); */

	/*all stuff!*/
	printf("%c%s %s %s %d %s %s\n", type, permisions, usr->pw_name,
	       grp->gr_name, size, formated_date, name);
}


int get_permisions(mode_t mode, char *buffer)
{
	int masks[3][4] = {
		{S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR},
		{S_IRWXG, S_IRGRP, S_IWGRP, S_IXGRP},
		{S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH}
	};
	char permision[4] = {'-', 'r', 'w', 'x'};
	int type_user;
	int mask_iter;

	for (type_user = 0; type_user < 3; type_user++)
	{
		/* if (mode & masks[type_user][0]) */
		/* { */
		/* 	*buffer = 'r'; */
		/* 	buffer++; */
		/* 	*buffer = 'w'; */
		/* 	buffer++; */
		/* 	*buffer = 'x'; */
		/* 	buffer++; */
		/* } */
		/* else */
		/* { */
			for (mask_iter = 1; mask_iter  < 4; mask_iter++)
			{
				if (mode & masks[type_user][mask_iter])
				{
					*buffer = permision[mask_iter];
					buffer++;
				}
				else
				{
					*buffer = permision[0];
					buffer++;
				}
			}
		/* } */
	}
	buffer = '\0';
	return (0);

}
