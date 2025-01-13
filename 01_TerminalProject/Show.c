#include <ncurses.h>

#define DX 2 
#define DY 2

**char getlines_from_file(char *filename)
{
	FILE *f;
	char *line = NULL;
	size_t len = 0;
	int nlines = 128;
	int i;
	char **lines = malloc(sizeof(char *) * nlines);

	f = fopen(filename, "r");
	if(f == NULL)
	{
		perror("fopen() ");
		return NULL;
	}

	i = 0;
	while((getline(&line, &len, f)) != -1)
	{
		lines[i] = line;
		i++;
		if(i >= nlines - 1)
		{
			nlines = lines * 2;
			new_lines = realloc(lines, sizeof(char *) * nlines);
			if(new_lines == NULL)
			{
				//TODO free
				perror("realloc() ");
				return NULL;
			}
			lines = new_lines;
		}
	}
}

int main(int argc, char **argv) 
{
	WINDOW *frame, *win;

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
