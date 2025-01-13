#include <ncurses.h>

#define DX 2 
#define DY 2

int main(int argc, char **argv) 
{
	WINDOW *win;

	initscr();
	noecho();
	cbreak();
	
	printw("File: %s", argv[1]);
	refresh();

	win = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
	box(win, 0, 0);
	wmove(win, 0, 1);
	//wrefresh(win);
	wgetch(win);
	endwin();

	return 0;
}
