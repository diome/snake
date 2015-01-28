CFLAGS=-Wall -ansi
LDFLAGS=-lncurses

snake: pos.o snake.o poison.o main.o
	gcc $(LDFLAGS) $^ -o $@

pos.o: pos.h pos.c
	gcc $(CFLAGS) -c pos.c -o pos.o

snake.o: snake.h snake.c
	gcc $(CFLAGS) -c snake.c -o snake.o
	
poison.o: poison.h poison.c
	gcc $(CFLAGS) -c poison.c -o poison.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
