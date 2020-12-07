#include "utils.h"

void updateDirection() {
    char ch;
    while((ch = getch()) != ERR) {
        switch(ch) {
            case 'h':
                currentDirection = lastDirection == right ? lastDirection : left;
                break;
            case 'j': 
                currentDirection = lastDirection == up ? lastDirection : down;
                break;
            case 'k': 
                currentDirection = lastDirection == down ? lastDirection : up;
                break;
            case 'l': 
                currentDirection = lastDirection == left ? lastDirection : right;
                break;
            default:
                break;
        }
    }
}
