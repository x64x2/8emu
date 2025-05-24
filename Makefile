# chip8 version
VERSION = 0.1

CC = cc
INC = -I/usr/include/SDL
CPPFLAGS = -DVERSION=\"$(VERSION)\"
CFLAGS = -std=c99 -pedantic -Wall -Os ${INC} ${CPPFLAGS}
LDFLAGS = -lSDL2

SRC = main.c chip8.h
OBJ = ${SRC:.c=.o}

all: c8

.c.o:
	${CC} -c ${CFLAGS} $<

c8: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

c8-static: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS} -static

test: main
	./chip8 -r tests/chip8-logo.ch8
	./chip8 -r tests/key.ch8
	./chip8 -r tests/beep.ch8

clean:
	rm -f main-static ${OBJ}

.PHONY: all clean
