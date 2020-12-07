#include "utils.h"

void drawSnake(struct snakeBody *head) {
    struct snakeBody *parser;
    parser = head;
    while(1) {
        if(screenMatrix[parser->row][parser->col] == 'x' || screenMatrix[parser->row][parser->col] == 'O')
            gameOver = 1;
        screenMatrix[parser->row][parser->col] = head == parser ? 'O' : 'o';
        if(parser->next == NULL)
            break;
        parser = parser->next;
    }
}
