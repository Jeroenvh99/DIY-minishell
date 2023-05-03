
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t	hash(char const *argc, size_t base);

int	main(int argc, char **argv)
{
	size_t	*hashes;
	size_t	i;

	hashes = malloc((argc - 1) * sizeof(size_t));
	i = 1;
	while (i < (size_t) argc - 1)
	{
		hashes[i - 1] = hash(argv[i], 200);
		i++;
	}
	i = 0;
	while (i < (size_t) argc - 1)
		printf("%zu ", hashes[i++]);
	printf("\n");
	free(hashes);
	return (0);
}
