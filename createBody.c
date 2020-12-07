#include "utils.h"

struct snakeBody *createBody(int row, int col) {
    struct snakeBody *temp;
    temp = (struct snakeBody *)malloc(sizeof(struct snakeBody));
    temp->row = row;
    temp->col = col;
    return temp;
}
