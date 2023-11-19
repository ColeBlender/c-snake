#ifndef UTILS_H
#define UTILS_H
#include <termios.h>

#define COLS 21
#define ROWS 21

typedef struct {
  int x;
  int y;
} Coordinate;

void terminal_to_game_mode(struct termios* oldT, int start);
void print_board();
void hide_start_message(int xDir, int yDir, int* startMessageVisible,
                        char startMessage[]);
void print_apple(Coordinate* appleCoords, Coordinate* snakeCoords,
                 int snakeLength, int startMessageVisible);
void move_snake(int xDir, int yDir, int* snakeLength, int* gameOver,
                Coordinate* snakeCoords, Coordinate* appleCoords);
void print_score(int* score, int appleX);
void sleep_time(int score);
void read_keyboard(int* xDir, int* yDir);
void show_game_over(int* quit, int* score, struct termios* oldT);
void end_game(struct termios* oldT);

#endif