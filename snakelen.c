#include "utils.h"

int snakelen(struct snakeBody *head) {
    int len = 1;
    while(head->next != NULL) {
        head = head->next;
        len++;
    }
    return len;
}
