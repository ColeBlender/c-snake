#include "utils.h"
#include <unistd.h>

void sleep_time(int score) {
  // speeds up by .0025 seconds every point
  int sleepTime = 125000 - score * 2500;

  // caps out at .05 seconds which occurs at 30 points
  sleepTime = sleepTime < 50000 ? 50000 : sleepTime;

  usleep(sleepTime);
}
