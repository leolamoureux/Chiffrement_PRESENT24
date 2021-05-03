CFLAGS = -Wall -g
CC = gcc

run : clean exe
	./exe f955b9 d1bd2d 

exe : main.o present.o attaque.o dechiffrement.o
	$(CC) main.o present.o attaque.o dechiffrement.o -lm -O3 -o exe


%.o : %.c present.h attaque.h dechiffrement.h
	$(CC) -c $<  $( CFLAGS )

valgrind : exe
	valgrind --leak-check = full ./exe 000000

clean :
	rm -f *.o
	rm -f chiffrer