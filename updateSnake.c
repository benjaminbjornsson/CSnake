#include "utils.h"

struct snakeBody *updateSnake(struct snakeBody *head) {
    struct snakeBody *newHead;
    int hstep = 0, vstep = 0;
    lastDirection = currentDirection;
    newHead = (struct snakeBody *)malloc(sizeof(struct snakeBody));
    newHead->next = head;
    if((currentDirection == up) || currentDirection == down)
        vstep = currentDirection == up ? -1 : 1;
    if((currentDirection == right) || currentDirection == left)
        hstep = currentDirection == right ? 1 : -1;
    newHead->row = head->row + vstep;
    newHead->col = head->col + hstep;
    if((apple.eaten = (apple.row == newHead->row) && (apple.col == newHead->col))) {
        return newHead;
    } else {
        while((head->next)->next != NULL) {
            head = head->next;
        }
        free(head->next);
        head->next = NULL;
        return newHead;
    }
}


