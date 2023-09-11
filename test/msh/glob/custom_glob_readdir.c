#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "libft.h"
#include "list_utils.h"
#include "ft_glob_utils.h"

#define N_TEST_PATHS 6

char const *paths[N_TEST_PATHS] = {"", "1", "1/1a", "1/1b", "1/1", "1/1/1"};
char const *names[N_TEST_PATHS][6] = {{".", "..", "1", "hi.txt", "hgfdhg", ""},
{".", "..", "1a", "1", "1b", "hello"}, {".", "..", "", "", "", ""}, {".", "..", "1d", "gh", "b", ""},
{".", "..", "1", "hi", "hgfdhg", ""}, {".", "..", "1", "hi.txt", "", ""}};
int const types[N_TEST_PATHS][6] = {{DT_DIR, DT_DIR, DT_DIR, DT_DIR, DT_REG, DT_REG},
{DT_DIR, DT_DIR, DT_REG, DT_DIR, DT_REG, DT_REG}, {DT_DIR, DT_DIR, DT_REG, DT_REG, DT_REG, DT_REG},
{DT_DIR, DT_DIR, DT_REG, DT_REG, DT_REG, DT_REG}, {DT_DIR, DT_DIR, DT_DIR, DT_REG, DT_REG, DT_REG},
{DT_DIR, DT_DIR, DT_REG, DT_REG, DT_REG, DT_REG}};

t_list *__wrap_glob_readdir(char const *path)
{
	t_list		*dirl;
	t_entry		*entry;
	int			i;
	int			dirn;

	dirn = 0;
	while (dirn < N_TEST_PATHS)
	{
		if (strcmp(paths[dirn], path) == 0)
			break;
		if (dirn < N_TEST_PATHS - 1)
			++dirn;
	}
	i = 0;
	dirl = NULL;
	while (i < N_TEST_PATHS)
	{
		if (strcmp(names[dirn][i], ""))
		{
			entry = malloc(sizeof(t_entry));
			if (!entry)
				return (list_clear(&dirl, free), NULL);
			entry->d_name[0] = '\0';
			ft_strlcpy(entry->d_name, names[dirn][i], NAME_MAX);
			entry->d_type = types[dirn][i];
			if (list_push_ptr(&dirl, entry) != 0)
				return (free(entry), list_clear(&dirl, free), NULL);
		}
		++i;
	}
	return (glob_sortdir(&dirl), dirl);
}