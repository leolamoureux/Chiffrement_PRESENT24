CFLAGS = -Wall -g
CC = gcc

run : clean chiffrer
	./chiffrer abcf00 000000

chiffrer : main.o PRESENT24.o
	$(CC) main.o PRESENT24.o -o chiffrer

%.o : %.c PRESENT24.h
	$(CC) -c $<  $( CFLAGS )

valgrind : chiffrer
	valgrind --leak-check = full ./chiffrer 000000

clean :
	rm -f *.o
	rm -f chiffrer