#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct Cell {
    /* 0 if the cell is dead. 1 otherwise */
    int alive;
    /* how many neighbors are alive */
    int count;
};

/* calculate the next iteration */
void step(int cols, int n, struct Cell *A);

/* count the number of alive neighbors */
void get_count(int cols, int n, struct Cell *A);

/* set the alive or dead condition of each cell */
void set_matrix(int n, struct Cell *A);

/* initialize ncurses */
void init_ncurses(void);

int main(void)
{

    time_t t;
    srand((unsigned) time(&t));

    init_ncurses();

    int lines = LINES;
    int cols = COLS;
    struct Cell A[lines * cols];

    int j=0;

    for (int i=0; i < lines * cols;) {
        A[i].alive = rand() % 2;
        if (A[i].alive)
            addch(ACS_DIAMOND);
        else
            addch(' ');
        if (++i % cols == 0)
            move(++j, 0);
    }

    char ch = ' ';
    while ((ch=getch()) != 'q') {
    /* while (1) { */

        clear();
        sleep(1);
        j = 0;

        for (int i=0; i < lines * cols;) {
            if (A[i].alive)
                addch(ACS_DIAMOND);
            else
                addch(' ');
            if (++i % cols == 0)
                move(++j, 0);
        }


        refresh();
        move(0, 0);
        step(cols, lines * cols, A);

    }

    endwin();

    return 0;
}

void step(int cols, int n, struct Cell *A) 
{

    /* get count */
    get_count(cols, n, A);
    set_matrix(n, A);
    
}

void get_count(int cols,int n, struct Cell *A) 
{

    /* count values */
    for (int i=0; i<n; i++)
        A[i].count = 0;

   for (int i=0; i<n; i++) {

        /* Check row above A[i] */
        if (i-cols >= 0) {

            if ((i-cols-1)/cols == (i-cols)/cols
                    && i-cols-1 >= 1
                    && A[i-cols-1].alive)
                A[i].count++;
            if (A[i-cols].alive)
                A[i].count++;
            if ((i-cols+1)/cols == (i-cols)/cols
                    && A[i-cols+1].alive)
                A[i].count++;

        }

        /* check beside element */
        if ((i%cols)-1 >= 0
                && A[i-1].alive)
            A[i].count++;
        if ((i%cols)+1 < cols
                && A[i+1].alive)
            A[i].count++;

        /* check row below */
        if (i+cols < n) {

            if ((i+cols-1)/cols == (i+cols)/cols
                    && i+cols-1 >= 1
                    && A[i+cols-1].alive)
                A[i].count++;
            if (A[i+cols].alive)
                A[i].count++;
            if ((i+cols+1)/cols == (i+cols)/cols
                    && A[i+cols+1].alive)
                A[i].count++;

        }
                

    }

}

void set_matrix(int n, struct Cell *A) 
{

    for (int i=0; i<n; i++) {
        /* Any live cell with two or three live neighbors survives. */
        if (A[i].alive
                && (A[i].count == 2 || A[i].count == 3))
                continue;
        else if (!A[i].alive
                && A[i].count == 3)
            A[i].alive = 1;
        else
            A[i].alive = 0;
    }

}

void init_ncurses(void) {
    initscr();
    timeout(0);
    raw();
    curs_set(0);
}
