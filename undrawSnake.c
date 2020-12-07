#include "utils.h"

void undrawSnake(struct snakeBody *head) {
    struct snakeBody *parser;
    parser = head;
    while(1) {
        screenMatrix[parser->row][parser->col] = ' ';
        if(parser->next == NULL)
            break;
        parser = parser->next;
    }
}
