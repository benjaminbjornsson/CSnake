objects = main.o createBody.o deinitSnake.o drawApple.o \
    drawScore.o drawScreen.o drawSnake.o initScreenMatrix.o \
    initSnake.o menu.o snakelen.o undrawApple.o undrawSnake.o \
    updateDirection.o updateSnake.o 
CSnake : $(objects)
	cc -o CSnake $(objects) /usr/lib/libncurses.dylib

$(objects) : utils.h

clean :
	rm CSnake $(objects)
