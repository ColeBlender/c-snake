#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static const int MAX_SCORES = 10;
static const int MAX_NAME_LENGTH = 4;

typedef struct {
  int score;
  char name[MAX_NAME_LENGTH + 1]; // +1 for null terminator
} ScoreEntry;

static int check_if_top_10_and_type_name(int* score, struct termios* oldT);

//
//
//
void show_game_over(int* quit, int* score, struct termios* oldT) {
  char gMessage[] = " GAME OVER! ";
  char rMessage[] = " Press R to play again! ";
  char qMessage[] = " Press Q to quit! ";

  // print gMessage
  printf("\e[H\e[%iB\e[%iC%s", ROWS / 2 + 3,
         COLS - (int)strlen(gMessage) / 2 + 2, gMessage);

  // see if top 10 score and prompt user to type name if so
  check_if_top_10_and_type_name(score, oldT);

  // print rMessage
  printf("\e[H\e[%iB\e[%iC%s", ROWS / 2 + 5,
         COLS - (int)strlen(rMessage) / 2 + 2, rMessage);
  // print qMessage
  printf("\e[%iB\e[%iD%s", 2,
         (int)(strlen(rMessage) + (strlen(qMessage) - strlen(rMessage)) / 2),
         qMessage);
  fflush(stdout);

  // infinite loop, exits only on 'r' or 'q'
  int ch;
  while (1) {
    ch = getchar();
    if (ch == 'r' || ch == 'R') {
      *score = 0;
      break;
    } else if (ch == 'q' || ch == 'Q') {
      *score = 0;
      *quit = 1;
      break;
    }
  }
}

//
//
//
static int check_if_top_10_and_type_name(int* score, struct termios* oldT) {
  FILE* file;
  char line[100];
  ScoreEntry scores[MAX_SCORES];
  int scoreCount = 0;

  file = fopen("high-scores.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(line, sizeof(line), file) && scoreCount < MAX_SCORES) {
    ScoreEntry entry;
    if (sscanf(line, "%*d. %d (%s)", &entry.score, entry.name) == 2) {
      entry.name[strlen(entry.name) - 1] = '\0';
      scores[scoreCount++] = entry;
    }
  }
  fclose(file);

  char newName[MAX_NAME_LENGTH + 1];

  // check if the new score is a top score
  int position = -1;
  for (int i = 0; i < scoreCount; i++) {
    if (*score > scores[i].score) {
      position = i;
      break;
    }
  }

  if (position != -1 || scoreCount < MAX_SCORES) {
    char highScoreMessage[] = " Great Score! Enter Name: ";

    // print highScoreMessage
    printf("\e[H\e[%iB\e[%iC%s", ROWS / 2 + 5,
           COLS - (int)strlen(highScoreMessage) / 2 + 2, highScoreMessage);
    // move cursor below highScoreMessage and clear space
    printf("\e[H\e[%iB\e[%iC      ", ROWS / 2 + 7, COLS - 6 / 2 + 2);
    // move cursor to beginning of space
    printf("\e[%iD", 5);
    // show the cursor
    printf("\e[?25h");
    fflush(stdout);

    char newName[5]; // buffer for the name
    int count = 0; // count of entered characters
    int ch; // character read from input

    // read characters one by one until Enter is pressed
    while (1) {
      ch = getchar();
      // check if enter is pressed and at least one character is present
      if (ch == '\n' && count > 0) {
        break;
      }
      if (ch == EOF) { // handle end-of-file character
        break;
      }
      if (ch == '\b' || ch == 127) { // handle backspace
        if (count > 0) {
          printf("\b \b"); // move back, print space, move back again
          count--;
        }
        continue;
      }
      if (ch == ' ' ||
          ch < 32) { // ignore space character and control characters
        continue;
      }
      // convert to uppercase
      ch = toupper(ch);
      if (count < 4) {
        newName[count++] = (char)ch;
        printf("%c", ch); // echo the character
      }
    }

    newName[count] = '\0';

    terminal_to_game_mode(oldT, 0);

    if (position == -1) {
      position = scoreCount;
    }

    for (int i = MAX_SCORES - 1; i >= position; i--) {
      if (i != 0) {
        scores[i] = scores[i - 1];
      }
    }
    scores[position].score = *score;
    strcpy(scores[position].name, newName);

    // write updated scores back to file
    file = fopen("high-scores.txt", "w");
    if (!file) {
      perror("Error opening file for writing");
      return 1;
    }

    if (scoreCount < MAX_SCORES) {
      scoreCount++;
    }

    for (int i = 0; i < scoreCount; i++) {
      fprintf(file, "%d. %d (%s)\n", i + 1, scores[i].score, scores[i].name);
    }

    fclose(file);

    printf("\e[H\e[%iB\e[%iC⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️", ROWS / 2 + 5,
           COLS - (int)strlen(highScoreMessage) / 2);
    fflush(stdout);
  }

  return 0;
}