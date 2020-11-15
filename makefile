CC=gcc
CFLAGS = -Wall -I sdk/SDL2/include # compilation opts.
LDFLAGS = -L sdk/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image  # link options
SRC=$(wildcard src/*.c) $(wildcard src/core/*.c) $(wildcard src/ui/*.c)
OBJ=$(SRC:.c=.o)
HDR=$(wildcard src/ui/*.h) $(wildcard src/core/*.h) $(wildcard src/ui/*.h)

metro : $(OBJ)		  # create an executable file under build of
	$(CC) -o  $@  $^  $(LDFLAGS) 

main.o: $(HDR)     
%.o: %.c
	$(CC) $(CFLAGS) -c  $^ -o $@

debug: ${OBJ}
	$(CC) -g -o  $@  $^  $(LDFLAGS)