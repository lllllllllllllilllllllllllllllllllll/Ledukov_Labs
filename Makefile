.PHONY: all clean
CFLAGS=-std=c18 -pedantic -Wall -Werror
CC=gcc
all: untiled7

main.o: main.c
			gcc -c -o main.o main.c

Read_Write_file.o: Read_Write_file.c
			$(CC) -c $(CFLAGS) $< -o $@

Speaks.o: Speaks.c
			$(CC) -c $(CFLAGS) $< -o $@

util.o: util.c
			$(CC) -c $(CFLAGS) $< -o $@

view.o: view.c
			$(CC) -c $(CFLAGS) $< -o $@

untiled7: main.o Speaks.o util.o Read_Write_file.c view.o
			$(CC) -o untiled7 $^

clean: rm -rf untiled7 *.o