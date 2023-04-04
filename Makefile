CC = gcc
FLAGS = -c -Wall -Werror -Wextra 

all: terminal.o 
	$(CC) *.o -o ./a.out 

terminal.o: terminal.c 
	$(CC) $(FLAGS) terminal.c 

clean:
	rm -rf *.o ./a.out