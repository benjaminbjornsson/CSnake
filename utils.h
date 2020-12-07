#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define WIDTH           20
#define HEIGHT          20
#define SNAKELEN        5

struct snakeBody {
    int row, col;
    struct snakeBody *next;
};

struct Apple {
    int row, col;
    int time;
    int eaten;
} apple;

enum direction {left = 0, up, right, down};

char screenMatrix[HEIGHT][WIDTH];
int currentDirection;
int lastDirection;
int highscore;

struct snakeBody *initSnake(void);
void initScreenMatrix(void);
void drawSnake(struct snakeBody *);
void undrawSnake(struct snakeBody *);
struct snakeBody *updateSnake(struct snakeBody *);
void drawScreen(void);
struct snakeBody *createBody(int, int);
void updateDirection(void);
void drawApple();
void undrawApple();
int snakelen(struct snakeBody *);
void drawScore(int);
void deinitSnake(struct snakeBody *);
int menu(void);

int gameOver;
