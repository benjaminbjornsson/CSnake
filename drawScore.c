#include "utils.h"

void drawScore(int score) {
    move(0, WIDTH - 8);
    printw(" --Score: %2d-- ", score);
    move(HEIGHT - 1, 2*WIDTH);
}

