#ifndef UTILS_H
#define UTILS_H
#include <termios.h>

#define COLS 40
#define ROWS 20
#define SLEEP_TIME 1000000 * .1 // right side of expression is how many seconds

typedef struct {
  int x;
  int y;
} Coordinate;

void init_terminal(struct termios* oldT);
void render_table();
void read_keyboard(int* xDir, int* yDir, int* quit);
void show_game_over();
void end_game(Coordinate* snakeCoords, struct termios* oldT);

#endif