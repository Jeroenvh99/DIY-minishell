#include "ft_hash.h"
#include "ft_stdio.h"
#include "ft_string.h"

#include <stdlib.h>

#define TABLE_SIZE	4

int	main(int argc, char **argv)
{
	t_hashtable	*table;
	char		*line;
	char		*value;
	int			i;

	if (argc % 2 == 0)
		return (1);
	table = hashtable_init(TABLE_SIZE);
	i = 1;
	while (i < argc)
	{
		ft_printf("%u ", hash(argv[i], TABLE_SIZE));
		if (hashtable_insert(table, argv[i], ft_strdup(argv[i + 1])) != 0)
			ft_dprintf(2, "oops\n");
		i += 2;
	}
	line = ft_getline(0);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		ft_printf("%u ", hash(line, TABLE_SIZE));
		value = hashtable_lookup(table, line);
		ft_printf("%s\n", value);
		free(line);
		line = ft_getline(0);
	}
	hashtable_destroy(&table, free);
	//system("leaks test");
	return (0);
}
