#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define DX 2 
#define DY 2

void free_lines(char **lines, int nlines)
{
	int i;
	for(i = 0; i < nlines; i++)
	{
		free(lines[i]);
	}
	free(lines);
}

int getlines_from_file(char ***lines, char *filename)
{
	FILE *f;
	char *line = NULL;
	size_t len = 0;
	int nlines = 128;
	int i;
	void *new_lines;
		
	*lines = calloc(sizeof(char *), nlines);
	if(*lines == NULL)
	{
		perror("calloc() ");
		return -1;
	}

	f = fopen(filename, "r");
	if(f == NULL)
	{
		free(*lines);
		perror("fopen() ");
		return -1;
	}

	i = 0;
	while((getline(&line, &len, f)) != -1)
	{
		(*lines)[i] = line;
		i++;
		if(i >= nlines - 1)
		{
			nlines = nlines * 2;
			new_lines = reallocarray(*lines, sizeof(char *), nlines);
			if(new_lines == NULL)
			{
				free_lines(*lines, nlines);
				fclose(f);
				perror("reallocarray() ");
				return -1;
			}
			*lines = new_lines;
		}

		line = NULL;
	}

	fclose(f);

	return i;
}

int main(int argc, char **argv) 
{
	WINDOW *frame, *win;
	char **lines;
	int nlines = 0;

	if(argc < 2)
	{
		fprintf(stderr, "Missing filename\n");
		return 1;
	}

	if((nlines = getlines_from_file(&lines, argv[1])) == -1)
	{
		return 1;
	}

	printf("%d\n", nlines);
	for(int i = 0; i < nlines; i++)
	{
		printf("%s", lines[i]);
	}

	initscr();
	noecho();
	cbreak();
	
	printw("File: %s", argv[1]);
	refresh();

	frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
	box(frame, 0, 0);
	wrefresh(frame);

	win = newwin(LINES - 2 * DY - 2, COLS - 2 * DX - 2, DY + 1, DX + 1);
	//wmove(win, 0, 1);
	//wrefresh(win);
	wgetch(win);
	endwin();

	return 0;
}
