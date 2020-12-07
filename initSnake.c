#include "utils.h"

struct snakeBody *initSnake(void) {
    struct snakeBody *head, *temp;
    int i;
    head = createBody(HEIGHT / 2, WIDTH / 2);
    head->next = createBody(HEIGHT / 2, WIDTH / 2 - 1);
    temp = head->next;
    for(i = 2; i < SNAKELEN; i++) {
        temp->next = createBody(HEIGHT / 2, WIDTH / 2 - i);
        temp = temp->next;
    }

    temp->next = NULL;

    return head;
}
