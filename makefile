CC=gcc
CFLAGS = -Wall -I sdk/SDL2/include # compilation opts.
LDFLAGS = -L sdk/SDL2/lib -lmingw32 -lSDL2main -lSDL2  # link options


metro : main.o			  # create an executable file under build of
	$(CC) ./build/main.o -o ./build/metro $(LDFLAGS)

main.o : src/main.c       # compile main.c`.
	$(CC) $(CFLAGS) -c ./src/main.c -o ./build/main.o

clean:
	rm -f ./build/metro.exe
	rm -f ./build/main.o