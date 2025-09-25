CC = gcc
OBJ = main.o linkedlist.o random.o newSleep.o terminal.o game.o terminalio.o
EXEC = escape
CFLAGS = -Wall -pedantic -ansi

${EXEC}: ${OBJ}
	${CC} ${OBJ} -o ${EXEC}
	
main.o: main.c linkedlist.h game.h random.h gamestate.h
	${CC} -c main.c ${CFLAGS}

linkedlist.o: linkedlist.h linkedlist.c
	${CC} -c linkedlist.c ${CFLAGS}

newSleep.o: newSleep.c newSleep.h
	${CC} -c newSleep.c ${CFLAGS}

random.o: random.c random.h
	${CC} -c random.c ${CFLAGS}

terminal.o: terminal.c terminal.h
	${CC} -c terminal.c ${CFLAGS}

game.o: game.c game.h terminalio.h gamestate.h linkedlist.h newSleep.h
	${CC} -c game.c ${CFLAGS}

terminalio.o: terminalio.c terminalio.h terminal.h
	${CC} -c terminalio.c ${CFLAGS}

clean:
	rm -f *.gch *.o ${EXEC}