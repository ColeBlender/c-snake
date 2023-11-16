#ifndef UTILS_H
#define UTILS_H
#include <termios.h>

#define COLS 20
#define ROWS 10
#define SLEEP_TIME 1000000 * .1 // right side of expression is how many seconds

typedef struct {
  int x;
  int y;
} Coordinate;

void init_terminal(struct termios* oldT);
void render_table();
void check_score(int* score, int appleX);
void draw_apple(Coordinate* appleCoords, Coordinate* snakeCoords,
                int snakeLength);
void move_snake(int xDir, int yDir, int* snakeLength, int* gameOver,
                Coordinate* snakeCoords, Coordinate* appleCoords, int* score);
void read_keyboard(int* xDir, int* yDir);
void show_game_over(int* quit);
void end_game(struct termios* oldT);

#endif