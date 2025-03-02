#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SUCCESS 0
#define NOARG_ERR 1
#define FOPEN_ERR 2
#define READFILE_ERR 3
#define WRITEFILE_ERR 4
#define FCLOSE_ERR 5
#define REMOVEFILE_ERR 6

#define SRCFD 100
#define DESTFD 101

void usage(char *prog)
{
	fprintf(stderr, "%s: Make file copy\n"\
			"Usage: %s <source file> <destination file>\n", prog, prog);
}

int main(int argc, char **argv)
{
	char ch;
	char *infile = argv[1], *outfile = argv[2];
	int srcfd, destfd;
	ssize_t n;

	if(argc < 3)
	{
		fprintf(stderr, "Missing argument\n");
		usage(argv[0]);
		return NOARG_ERR;
	}

	srcfd = open(argv[1], O_RDONLY);
	if(srcfd == -1)
	{
		perror("Source file opening error ");
		return FOPEN_ERR;
	}

	destfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
	if(destfd == -1)
	{
		perror("Destination file opening error");
		close(srcfd);
		return FOPEN_ERR;
	}

	if(srcfd != SRCFD)
	{
		dup2(srcfd, SRCFD);
		close(srcfd);
	}
	if(destfd != DESTFD)
	{
		dup2(destfd, DESTFD);
		close(destfd);
	}

	while((n = read(SRCFD, &ch, sizeof(char))) > 0)
	{
		if(write(DESTFD, &ch, sizeof(char)) == -1)
		{
			perror("Writing to file error ");
			close(SRCFD);
			close(DESTFD);
	
			unlink(outfile);

			return WRITEFILE_ERR;
		}
	}
	if(n == -1)
	{
		perror("Reading file error ");
		close(SRCFD);
		close(DESTFD);

		unlink(outfile);

		return READFILE_ERR;
	}

	if(close(SRCFD) == -1)
	{
		perror("Source file close error ");
		close(DESTFD);
		unlink(outfile);

		return FCLOSE_ERR;
	}
	if(close(DESTFD) == -1)
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
