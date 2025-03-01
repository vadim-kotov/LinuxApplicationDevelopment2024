#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define SUCCESS 0
#define NOARG_ERR 1
#define FOPEN_ERR 2
#define READFILE_ERR 3
#define WRITEFILE_ERR 4
#define FCLOSE_ERR 5
#define REMOVEFILE_ERR 6

void usage(char *prog)
{
	fprintf(stderr, "%s: Make file copy\n"\
			"Usage: %s <source file> <destination file>\n", prog, prog);
}

int main(int argc, char **argv)
{
	FILE *src, *dest;
	char ch;
	char *infile = argv[1], *outfile = argv[2];

	if(argc < 3)
	{
		fprintf(stderr, "Missing argument\n");
		usage(argv[0]);
		return NOARG_ERR;
	}

	src = fopen(argv[1], "r");
	if(src == NULL)
	{
		perror("Source file opening error ");
		return FOPEN_ERR;
	}

	dest = fopen(argv[2], "w");
	if(dest == NULL)
	{
		perror("Destination file opening error");
		fclose(src);
		return FOPEN_ERR;
	}

	while((ch = fgetc(src)) != EOF)
	{
		if((fputc(ch, dest)) == EOF)
		{
			ferror(dest);
			perror("Writing to file error ");
			fclose(src);
			fclose(dest);
	
			unlink(outfile);

			return WRITEFILE_ERR;
		}
	}
	if(ferror(src))
	{
		perror("Reading file error ");
		fclose(src);
		fclose(dest);

		unlink(outfile);

		return READFILE_ERR;
	}

	if(fclose(src))
	{
		perror("Source file close error ");
		fclose(dest);
		unlink(outfile);

		return FCLOSE_ERR;
	}
	if(fclose(dest))
	{
		perror("Destination file close error ");
		return FCLOSE_ERR;
	}

	if(unlink(infile))
	{
		perror("File deletion error");
		return REMOVEFILE_ERR;
	}

	return SUCCESS;
}
