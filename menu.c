#include "utils.h"

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
    printw("j - down");
    move(10, 15);
    printw("k - up");
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
