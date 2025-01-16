#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <limits.h>

#define DX 2 
#define DY 2
#define NLINES (LINES - 2 * DY - 2)
#define NCOLS (COLS - 2 * DX - 2)

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
    free(line);

    fclose(f);

    return i;
}

int main(int argc, char **argv) 
{
    WINDOW *frame, *win;
    char **lines;
    int nlines = 0;
    int fline = 0, fcol = 0;
    int c = 0;
    int refresh;

    if(argc < 2)
    {
        fprintf(stderr, "Missing filename\n");
        return 1;
    }

    if((nlines = getlines_from_file(&lines, argv[1])) == -1)
    {
        return 1;
    }

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    
    printw("File: %s", argv[1]);
    refresh();

    frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
    box(frame, 0, 0);
    wrefresh(frame);

    win = newwin(NLINES, NCOLS, DY + 1, DX + 1);
    keypad(win, TRUE);
    wmove(win, 0, 0);
    while(c != 27)
    {
        werase(win);
        wmove(win, 0, 0);
        for(int line = fline; line < fline + NLINES && line < nlines; line++)
        {
            if(fcol < (int)strlen(lines[line]))
            {
                wprintw(win, "%4d:%.*s", line + 1, NCOLS - 5, lines[line] + fcol);
            }
            else
            {
                wprintw(win, "%4d:\n", line + 1);
            }
        }

        refresh = 0;
        while(!refresh)
        {
            c = wgetch(win);
            if(c == 27)
                break;

            refresh = 1;    
            switch(c)
            {
                case KEY_UP:
                    if(fline > 0)
                        fline--;
                    break;

                case KEY_DOWN:
                    if(fline + NLINES < nlines)
                        fline++;
                    break;

                case KEY_LEFT:
                    if(fcol > 0)
                        fcol--;
                    break;

                case KEY_RIGHT:
                    if(fcol < INT_MAX)
                        fcol++;
                    break;

                default:
                    refresh = 0;
            }
        }

        if(c != 27)
        {
            box(frame, 0, 0);
            wmove(frame, 0, 1);
            wprintw(frame, "%s", keyname(c));
            wrefresh(frame);
        }
    }
    endwin();

    free_lines(lines, nlines);

    return 0;
}
