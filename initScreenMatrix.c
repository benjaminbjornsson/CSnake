#include "utils.h"

void initScreenMatrix(void) {
    int i, j;
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++)
            screenMatrix[i][j] = (i == 0 || i == HEIGHT - 1) || (j == 0 || j == WIDTH - 1) ? 'x': ' ';
}
