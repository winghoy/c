#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics.h"

const int WINDOW_OFFSET = 25;
const int WINDOW_LENGTH = 550;
const int SQUARE_SIZE = 50;
const int GRID_SIZE = 12;
const int GRID_OFFSET = 1;

// Direction of robot
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;

const int NUMBER_OF_POINTS = 3;

void starting_position(int *x, int *y, int **grid) {
    // Set starting position to 1
    *((*(grid + *y/SQUARE_SIZE + GRID_OFFSET)) + *x/SQUARE_SIZE + GRID_OFFSET) = 9;

    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE, *x + WINDOW_OFFSET};
    int y_coords[] = {*y + WINDOW_OFFSET, *y + WINDOW_OFFSET + (SQUARE_SIZE / 2), *y + WINDOW_OFFSET + SQUARE_SIZE};

    foreground();
    setColour(black);
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
    sleep(500);
}

void coordinates_to_grid(int *x, int *y, int *gridX, int *gridY) {
    // Convert the pixel location to grid coordinates
    *gridX = *x/SQUARE_SIZE + GRID_OFFSET;
    *gridY = *y/SQUARE_SIZE + GRID_OFFSET;
}

void draw_background() {
    setWindowSize(WINDOW_LENGTH, WINDOW_LENGTH);
    background();
    setColour(black);

    // Draw a 10x10 square grid
    for (int column = 0 ; column < 11 ; column++) {
        drawLine((column * SQUARE_SIZE) + WINDOW_OFFSET, WINDOW_OFFSET, (column * SQUARE_SIZE) + WINDOW_OFFSET, WINDOW_LENGTH - WINDOW_OFFSET);
    }

    for (int row = 0 ; row < 11 ; row++) {
        drawLine(WINDOW_OFFSET, (row * SQUARE_SIZE) + WINDOW_OFFSET, WINDOW_LENGTH - WINDOW_OFFSET, (row * SQUARE_SIZE) + WINDOW_OFFSET);
    }
}

void draw_robot(int *x, int *y) {
    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE, *x + WINDOW_OFFSET};
    int y_coords[] = {*y + WINDOW_OFFSET, *y + WINDOW_OFFSET + (SQUARE_SIZE / 2), *y + WINDOW_OFFSET + SQUARE_SIZE};

    foreground();
    setColour(black);
    // Draw a triangle robot
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
}

void move_north(int *x, int *y, int *gridX, int *gridY, int** grid) {
    // Move the robot up by 1 in the grid
    coordinates_to_grid(x, y, gridX, gridY);
    grid[*gridY][*gridX] = 0;
    *y -= SQUARE_SIZE;
    coordinates_to_grid(x, y, gridX, gridY);
    grid[*gridY][*gridX] = 1;

    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE/2, *x + WINDOW_OFFSET + SQUARE_SIZE};
    int y_coords[] = {*y + WINDOW_OFFSET + SQUARE_SIZE, *y + WINDOW_OFFSET, *y + WINDOW_OFFSET + SQUARE_SIZE};

    clear();
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
}

void move_east(int *x, int *y, int** grid) {
    // Move the robot right by 1 in the grid
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 0;
    *x += SQUARE_SIZE;
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 1;
    

    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE, *x + WINDOW_OFFSET};
    int y_coords[] = {*y + WINDOW_OFFSET, *y + WINDOW_OFFSET + (SQUARE_SIZE / 2), *y + WINDOW_OFFSET + SQUARE_SIZE};

    clear();
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
}

void move_south(int *x, int *y, int** grid) {
    // Move the robot down by 1 in the grid
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 0;
    *y += SQUARE_SIZE;
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 1;

    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE/2, *x + WINDOW_OFFSET + SQUARE_SIZE};
    int y_coords[] = {*y + WINDOW_OFFSET, *y + WINDOW_OFFSET + SQUARE_SIZE, *y + WINDOW_OFFSET};

    clear();
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
}

void move_west(int *x, int *y, int** grid) {
    // Move the robot left by 1 in the grid
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 0;
    *x -= SQUARE_SIZE;
    *((*(grid + *x/SQUARE_SIZE + GRID_OFFSET)) + *y/SQUARE_SIZE + GRID_OFFSET) = 1;

    int x_coords[] = {*x + WINDOW_OFFSET, *x + WINDOW_OFFSET + SQUARE_SIZE, *x + WINDOW_OFFSET + SQUARE_SIZE};
    int y_coords[] = {*y + WINDOW_OFFSET + SQUARE_SIZE/2, *y + WINDOW_OFFSET, *y + WINDOW_OFFSET + SQUARE_SIZE};

    clear();
    fillPolygon(NUMBER_OF_POINTS, x_coords, y_coords);
}

void forward(bool *move, int x, int y, int *direction, int **grid) {
    // Move forward in the current direction
    *move = true;
    switch(*direction) {
    case NORTH:
        //move_north(&x, &y, grid);
        break;
    case EAST:
        move_east(&x, &y, grid);
        break;
    case SOUTH:
        move_south(&x, &y, grid);
        break;
    case WEST:
        move_west(&x, &y, grid);
        break;
    default:
        break;
    }
    *move = false;
}

void turn_left(int x, int y, int *direction, int **grid) {
    // Rotate the robot to the left in the same spot
    switch(*direction) {
    case NORTH:
        move_west(&x, &y, grid);
        break;
    case EAST:
        //move_north(&x, &y, grid);
        break;
    case SOUTH:
        move_east(&x, &y, grid);
        break;
    case WEST:
        move_south(&x, &y, grid);
        break;
    default:
        break;
    }
}

void turn_right(int x, int y, int *direction, int **grid) {
    // Rotate the robot to the right in the same spot
    switch(*direction) {
    case NORTH:
        move_east(&x, &y, grid);
        break;
    case EAST:
        move_south(&x, &y, grid);
        break;
    case SOUTH:
        move_west(&x, &y, grid);
        break;
    case WEST:
        //move_north(&x, &y, grid);
        break;
    default:
        break;
    }
}

bool can_move_forward(int **grid) {
    int object = grid[]
}

int main() {
    // Initial position and direction of the robot
    int robotX = 100;
    int robotY = 100;
    int direction = EAST;
    bool move = true;
    int gridX, gridY;

    // 2D array of 10x10 grid to track position of robot & markers
    int** grid = (int**)malloc(GRID_SIZE * sizeof(int*));
    for (int i = 0; i < GRID_SIZE; i++) {
        grid[i] = (int*)malloc(GRID_SIZE * sizeof(int));
    }

    for (int i = 0 ; i < GRID_SIZE ; i++) {
        for (int j = 0 ; j < GRID_SIZE ; j++) {
            if (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1) {
                grid[i][j] = 2; // Value of 2 represents the outer wall
            } else {
                grid[i][j] = 0; // Value of 0 represents empty cell
            }
        }
    }
    
    draw_background();
    starting_position(&robotX, &robotY, grid);

    for (int i = 0 ; i < 2 ; i++) {
        foreground();
        setColour(black);
        move_north(&robotX, &robotY, &gridX, &gridY, grid);
        /*for (int i = 0 ; i < GRID_SIZE ; i++) {
            for (int j = 0 ; j < GRID_SIZE ; j++) {
                printf("%d", grid[i][j]);
            }
            printf("\n");
        } */
        sleep(500);
    }

    /*for (int i = 0 ; i < GRID_SIZE ; i++) {
        for (int j = 0 ; j < GRID_SIZE ; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }*/

    free(grid);
    return 0;
}