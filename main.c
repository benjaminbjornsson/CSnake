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
int currentDirection = right;
int lastDirection = right;
int highscore = 0;

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

int menu() {
    int menu = 1;
    char ch;
    drawScreen();
    move(5, 15);
    printw("New game");
    move(6, 15);
    printw("Quit");
    move(8, 15);
    printw("h - left");
    move(9, 15);
    printw("j - up");
    move(10, 15);
    printw("k - down");
    move(11, 15);
    printw("l - right");
    move(13, 7);
    printw("Press enter to continue");
    move(HEIGHT - 1, 2 * WIDTH - 1);

    while(1) {
        switch(ch = getch()) {
            case 'j':
                menu = (menu + 1) % 2;
                break;
            case 'k':
                menu = (menu - 1) % 2;
                break;
            case '\n':
                return menu;
            default:
                break;
        }
        if(menu) {
            move(5, 13);
            addch('>');
            move(6, 13);
            addch(' ');
        } else {
            move(5, 13);
            addch(' ');
            move(6, 13);
            addch('>');
        }
        move(0, WIDTH - 10);
        printw(" --Highscore: %2d-- ", highscore);
        move(HEIGHT - 1, 2 * WIDTH - 1);
    }
}

void deinitSnake(struct snakeBody *head) {
    if(head->next == NULL)
        return;
    deinitSnake(head->next);
    free(head);
}

void drawScore(int score) {
    move(0, WIDTH - 8);
    printw(" --Score: %2d-- ", score);
    move(HEIGHT - 1, 2*WIDTH);
}

int snakelen(struct snakeBody *head) {
    int len = 1;
    while(head->next != NULL) {
        head = head->next;
        len++;
    }
    return len;
}

void undrawApple() {
    screenMatrix[apple.row][apple.col] = ' ';
}

void drawApple() {
    if(apple.time > 0 && !apple.eaten) {
        screenMatrix[apple.row][apple.col] = '@';
        apple.time--;
    } else {
        apple.time = 25;
        apple.eaten = 0;
        do {
            apple.row = rand() % HEIGHT;
            apple.col = rand() % WIDTH;
        } while(screenMatrix[apple.row][apple.col] != ' ');
        screenMatrix[apple.row][apple.col] = '@';
    }
}

void updateDirection() {
    char ch;
    while((ch = getch()) != ERR) {
        switch(ch) {
            case 'h':
                currentDirection = lastDirection == right ? lastDirection : left;
                break;
            case 'j': 
                currentDirection = lastDirection == down ? lastDirection : up;
                break;
            case 'k': 
                currentDirection = lastDirection == up ? lastDirection : down;
                break;
            case 'l': 
                currentDirection = lastDirection == left ? lastDirection : right;
                break;
            default:
                break;
        }
    }
}

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

struct snakeBody *createBody(int row, int col) {
    struct snakeBody *temp;
    temp = (struct snakeBody *)malloc(sizeof(struct snakeBody));
    temp->row = row;
    temp->col = col;
    return temp;
}

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

void undrawSnake(struct snakeBody *head) {
    struct snakeBody *parser;
    parser = head;
    for(;;) {
        screenMatrix[parser->row][parser->col] = ' ';
        if(parser->next == NULL)
            break;
        parser = parser->next;
    }
}

void initScreenMatrix(void) {
    int i, j;
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++)
            screenMatrix[i][j] = (i == 0 || i == HEIGHT - 1) || (j == 0 || j == WIDTH - 1) ? 'x': ' ';
}

void drawScreen() {
    int i, j;
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            move(i, 2 * j);
            addch(screenMatrix[i][j]);
        }
    }
}
