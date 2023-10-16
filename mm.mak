# Compiler Flags
CC = tcc
CCFLAGS += -Wall -Wextra
UNAME := $(shell uname)
ifeq ($(UNAME), s0mt0chukwu)
LDFLAGS = -framework SDL -framework GLUT
else
LDFLAGS = -lGL -lglut
endif

all: play

play: SRC.c
	$(CC) $(CCFLAGS) SRC.c -o play $(LDFLAGS)

clean:
	rm -f play
