#include "utils.h"

void drawApple() {
    if(apple.time > 0 && !apple.eaten) {
        screenMatrix[apple.row][apple.col] = '@';
        apple.time--;
    } else {
        apple.time = 25;
        apple.eaten = 0;
        do {
            apple.row = rand() % HEIGHT;
            apple.col = rand() % WIDTH;
        } while(screenMatrix[apple.row][apple.col] != ' ');
        screenMatrix[apple.row][apple.col] = '@';
    }
}

