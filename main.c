#include "utils.h"

char screenMatrix[HEIGHT][WIDTH];
int currentDirection = right;
int lastDirection = right;
int highscore = 0;
int gameOver = 0;

int main() {
    struct snakeBody *head;
    WINDOW *stdscr;
    int len, speed, score;

    stdscr = initscr();
    nodelay(stdscr, TRUE);
    
    while(1) {
        currentDirection = right;
        apple.time = 0;
        head = initSnake();

        initScreenMatrix();
        if(!menu())
            break;
        clear();

        while(!gameOver) {
            updateDirection();
            head = updateSnake(head);
            len = snakelen(head);
            score = len - SNAKELEN;

            drawSnake(head);
            drawApple();
            drawScreen();
            drawScore(score);
            refresh();

            undrawSnake(head);
            undrawApple();
            speed = len < 25 ? score : 20;
            usleep(250000 - speed * 10000);
        }
        highscore = score > highscore ? score : highscore;
        clear();
        gameOver = 0;
        deinitSnake(head);
    }
    nodelay(stdscr, FALSE);
    endwin();
}

