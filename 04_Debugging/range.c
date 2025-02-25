#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void usage(char *prog)
{
	fprintf(stderr, "%s: generate math sequence\n\t"\
			"Usage: %s arg1 [arg2 [arg3]]\n", prog, prog);
}

int get_arg(char *prog, char *src, long int *dest)
{
	errno = 0;
	*dest = strtol(src, NULL, 10);
	if(errno != 0)
	{
		perror("Invalid argument ");
		usage(prog);
		return 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	long int M = 0, N = 0, S = 1;
	long int args[3];
	long int i;

	if(argc < 2 || argc > 4)
	{
		usage(argv[0]);
		return 1;
	}	

	if(args == NULL)
	{
		perror("Memory allocation error ");
		return 1;
	}
	for(i = 1; i < argc; i++)
	{
		if(get_arg(argv[0], argv[i], &(args[i-1])))
		{
			return 1;
		}
	}

	if(argc == 2)
	{
		N = args[0];
	}
	else if(argc == 3)
	{
		M = args[0];
		N = args[1];
	}
	else if(argc == 4)
	{
		M = args[0];
		N = args[1];
		S = args[2];
	}

	for(i = M; i < N; i += S)
	{
		printf("%ld\n", i);
	}

	return 0;
}
