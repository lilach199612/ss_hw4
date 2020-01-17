CC=gcc
FLAGS= -Wall -g

all: frequency
frequency: main.c main.h
	$(CC) $(FLAGS)  main.c main.h -o frequency

.PHONY: clean all

clean:
	rm -f frequency

