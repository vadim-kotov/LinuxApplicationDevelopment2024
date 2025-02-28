#include <stdio.h>
#include <errno.h>

void usage(char *prog)
{
	fprintf(stderr, "Make file copy\n"\
			"Usage: %s <source file> <destination file>\n", prog);
}

int main(int argc, char **argv)
{
	FILE *src, *dest;
	char ch;

	if(argc < 3)
	{
		fprintf(stderr, "Missing argument\n");
		usage(argv[0]);
		return 1;
	}

	src = fopen(argv[1], "r");
	if(src == NULL)
	{
		perror("Source file opening error ");
		return 1;
	}

	dest = fopen(argv[2], "w");
	if(dest == NULL)
	{
		perror("Destination file opening error");
		fclose(src);
		return 1;
	}

	while((ch = fgetc(src)) != EOF)
	{
		fputc(ch, dest);
	}

	fclose(src);
	fclose(dest);

	return 0;
}
