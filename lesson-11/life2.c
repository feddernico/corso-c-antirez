#include <stdio.h>
#include <unistd.h>

#define GRID_COLS 20
#define GRID_ROWS 20
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*'
#define DEAD '.'

/* Translate the specified x,y grid point into the index in 
 * the linear array. This function implements wrapping, so both negative
 * and positive coordinates that are out of the grid will wrap around. */
int cell_to_index(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }
    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }
    
    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (y >= GRID_ROWS) y = y % GRID_ROWS;

    return y*GRID_COLS+x;
}

/* The function sets the specified cell at x,y to the specified state. */
void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_index(x,y)] = state; 
}

/* The function returns the state of the grid at x,y. */
char get_cell(char *grid, int x, int y) {
    return grid[cell_to_index(x,y)];
}

/* Show the grid on the screen, clearing the terminal using the
 * required VT100 escape sequence. */
void print_grid(char *grid) {
    printf("\x1b[3J\x1b[H\x1b[2J");
    for (int y = 0; y < GRID_ROWS; y++) { 
        for (int x = 0; x < GRID_COLS; x++) {
            printf("%c", (get_cell(grid,x,y)));
        }
        printf("\n");
    }
}

/* Set all the grid cells to the specified state.*/
void set_grid(char *grid, char state) {
    for (int y = 0; y < GRID_ROWS; y++) { 
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid,x,y,state);
        }
    }
}

/* Return the number of living cells neighbors of x,y. */
int count_living_neighbors(char *grid, int x, int y) {
    int alive = 0;

    for (int yo = -1; yo <= 1; yo++) {
        for (int xo = -1; xo <= 1; xo++) {
            if (xo == 0 && yo == 0) continue;
            if (get_cell(grid,x+xo,y+yo) == ALIVE) alive++;
            
        }
    }
    return alive;
}

/* Compute the new state of Game of Life according to its rules. */
void compute_new_state(char *old, char *new) {
    for (int y = -1; y <= GRID_ROWS; y++) {
        for (int x = -1; x <= GRID_COLS; x++) {
            int n_alive = count_living_neighbors(old,x,y);
            int new_state = DEAD;
            if (get_cell(old,x,y) == ALIVE) {
                if (n_alive == 2 || n_alive == 3)
                    new_state = ALIVE;
            } else {
                if (n_alive == 3)
                    new_state = ALIVE;
            }
            set_cell(new,x,y,new_state);
        }
    }

}


int main(void) {
    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];
    set_grid(old_grid,DEAD);
    set_cell(old_grid,10,10,ALIVE);
    set_cell(old_grid,9,10,ALIVE);
    set_cell(old_grid,11,10,ALIVE);
    set_cell(old_grid,11,9,ALIVE);
    set_cell(old_grid,10,8,ALIVE);
    // implement an upgraded logic to improve what was done in lesson 8
    // you can remove the duplicated call to compute_new_state, print_grid and usleep by adding two pointers, 
    // one to the old and one to the new grid.
    char *old = old_grid;
    char *new = new_grid;
    while(1) {
        compute_new_state(old_grid,new_grid);
        print_grid(new_grid);
        usleep(100000);
        compute_new_state(new_grid,old_grid);
        print_grid(old_grid);
        usleep(100000);
    }
    return 0;

}

