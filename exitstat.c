#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	stat;

	printf("%d\n", getpid());
	if (argc < 2 || argc > 3)
		return (1);
	stat = atoi(argv[1]);
	if (argc == 3 && strncmp(argv[2], "loop", 5) == 0)
		while (1)
			;
	return (stat);
}
