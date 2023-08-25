#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

struct dirent *__wrap_readdir(DIR *dirp)
{
	static int calls = 0;
	struct dirent *dirent;

	dirent = malloc(sizeof(dirent));
	if (calls == 0)
		dirent->d_name[0] = '.';
		dirent->d_name[1] = '/';
		dirent->d_name[2] = '1';
		dirent->d_name[3] = '\0';
	// else if (calls == 1)
	// 	dirent->d_name = "./1a";
	// else if (calls == 2)
	// 	dirent->d_name = "./1/1";
	// else if (calls == 3)
	// 	dirent->d_name = "./1/1a";
	++calls;
	return dirent;
}