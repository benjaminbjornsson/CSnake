#include "utils.h"

void drawScreen() {
    int i, j;
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            move(i, 2 * j);
            addch(screenMatrix[i][j]);
        }
    }
}
