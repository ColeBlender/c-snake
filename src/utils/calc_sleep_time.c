#include "utils.h"

int calc_sleep_time(int score) {
  int sleepTime = 125000 - score * 2500;

  return sleepTime < 50000 ? 50000 : sleepTime;
}