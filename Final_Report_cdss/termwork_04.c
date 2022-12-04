#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

struct myfile
{
	char filetype;
	char *permissions;
	int links;
	char *owner;
	char *group;
	long size;
	char *modified;
	char *filename;
};

char *print_group(gid_t gid);
char *print_perm(int perm);
char *print_user(uid_t uid);
char print_filetype(int);
void print_myfile(struct myfile *);
char *print_last_modified(time_t t);

int main(void)
{
	DIR *dirp;
	struct dirent *dir;
	struct stat sp;
	int stat_status;
	struct tm *tm;
	char mtime[80];
	struct tm lt;

	struct myfile m[100];
	struct myfile myf;

	int count = 0;
	int total = 0;

	dirp = opendir(".");

	if (dirp == NULL)
	{
		printf("No such directory!!!\n");
		exit(1);
	}

	while ((dir = readdir(dirp)) != NULL)
	{
		stat(dir->d_name, &sp);
		// printf(" %s	", dir->d_name);
		myf.filetype = print_filetype(sp.st_mode);
		myf.filename = dir->d_name;
		myf.size = sp.st_size;
		myf.links = sp.st_nlink;
		myf.group = print_group(sp.st_gid);
		myf.owner = print_user(sp.st_uid);
		myf.permissions = print_perm(sp.st_mode);

		myf.modified = print_last_modified(sp.st_mtime);

		// printf("%s\n", myf.modified);
		// print_myfile(&myf);
		m[count++] = myf;
		total += sp.st_blocks;
	}

	// Now Displaying everything

	printf("total %d\n", total / 2);
	int j = 0;
	while (j < count)
	{
		print_myfile(&m[j]);
		j++;
	}

	return 0;
}

char *print_last_modified(time_t t)
{
	int i;
	char *mtime = (char *)malloc(sizeof(char) * 13);
	struct tm *lt;
	// time(&t);
	lt = localtime(&t);
	char *temp = asctime(lt);

	strftime(mtime, 12, "%b %d %H:%M", lt);

	for (i = 4; i < 16; i++)
	{
		mtime[i - 4] = *(temp + i);
	}
	*(mtime + 12) = '\0';

	return mtime;
}

char print_filetype(int type)
{

	if ((type & S_IFSOCK) == S_IFSOCK)
		return 's';
	else if ((type & S_IFLNK) == S_IFLNK)
		return 'l';
	else if ((type & S_IFREG) == S_IFREG)
		return '-';
	else if ((type & S_IFBLK) == S_IFBLK)
		return 'b';
	else if ((type & S_IFDIR) == S_IFDIR)
		return 'd';
	else if ((type & S_IFCHR) == S_IFCHR)
		return 'c';
	else if ((type & S_IFIFO) == S_IFIFO)
		return 'p';
	else
		return '-';
}

void print_myfile(struct myfile *mf)
{
	printf(" %c%s %d %s %s %6ld %s %s", mf->filetype, mf->permissions, mf->links, mf->group, mf->owner, mf->size, mf->modified, mf->filename);
	printf("\n");
}

char *print_perm(int perm)
{
	char *str = (char *)malloc(sizeof(char) * 10);
	*(str + 0) = ((perm & S_IRUSR) == S_IRUSR) ? 'r' : '-';
	*(str + 1) = ((perm & S_IWUSR) == S_IWUSR) ? 'w' : '-';
	*(str + 2) = ((perm & S_IXUSR) == S_IXUSR) ? 'x' : '-';
	*(str + 3) = ((perm & S_IRGRP) == S_IRGRP) ? 'r' : '-';
	*(str + 4) = ((perm & S_IWGRP) == S_IWGRP) ? 'w' : '-';
	*(str + 5) = ((perm & S_IXGRP) == S_IXGRP) ? 'x' : '-';
	*(str + 6) = ((perm & S_IROTH) == S_IROTH) ? 'r' : '-';
	*(str + 7) = ((perm & S_IWOTH) == S_IWOTH) ? 'w' : '-';
	*(str + 8) = ((perm & S_IXOTH) == S_IXOTH) ? 'x' : '-';
	*(str + 9) = '\0';
	/*
	   S_IWUSR   00200   Write by owner.
	   S_IXUSR   00100   Execute (search if	a directory) by	owner.

	   S_IRWXG   00070   Read, write, execute by group.
	   S_IRGRP   00040   Read by group.
	   S_IWGRP   00020   Write by group.
	   S_IXGRP   00010   Execute by	group.
	   S_IRWXO   00007   Read, write, execute (search) by others.
	   S_IROTH   00004   Read by others.
	   S_IWOTH   00002   Write by others
	   S_IXOTH   00001   Execute by	others.
	*/

	return str;
}
char *print_user(uid_t uid)
{
	struct passwd *p;
	p = getpwuid(uid);
	return p->pw_name;
}
char *print_group(gid_t gid)
{

	struct group *g;
	g = getgrgid(gid);
	return g->gr_name;
}
