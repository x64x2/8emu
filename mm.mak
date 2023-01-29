# Compiler Flags
CC = gcc
CCFLAGS += -Wall -Wextra
UNAME := $(shell uname)
ifeq ($(UNAME), Eric)
LDFLAGS = -framework SDL -framework GLUT
else
LDFLAGS = -lGL -lglut
endif

all: play

play: chip8.c play.c
	$(CC) $(CCFLAGS) chip8.c play.c -o play $(LDFLAGS)

clean:
	rm -f play
