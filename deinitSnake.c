#include "utils.h"

void deinitSnake(struct snakeBody *head) {
    if(head->next == NULL)
        return;
    deinitSnake(head->next);
    free(head);
}
