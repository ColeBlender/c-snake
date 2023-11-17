#ifndef UTILS_H
#define UTILS_H
#include <termios.h>

#define COLS 20
#define ROWS 20

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
                Coordinate* snakeCoords, Coordinate* appleCoords);
int calc_sleep_time(int score);
void read_keyboard(int* xDir, int* yDir);
void show_game_over(int* quit, int* score);
void end_game(struct termios* oldT);

#endif