#include <dirent.h>
#include <stdio.h>

struct dirent *__wrap_readdir(DIR *dirp)
{
	printf("Das ist eine test.\n");
	return NULL;
}