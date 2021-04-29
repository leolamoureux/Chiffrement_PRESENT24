CFLAGS = -Wall -g
CC = gcc

run : clean chiffrer
	./chiffrer 000000 000000
	./chiffrer ffffff 000000
	./chiffrer 000000 ffffff
	./chiffrer f955b9 d1bd2d 

chiffrer : main.o PRESENT24.o dechiffrement.o attaque.o
	$(CC) main.o PRESENT24.o dechiffrement.o attaque.o -o chiffrer


%.o : %.c PRESENT24.h dechiffrement.h attaque.h
	$(CC) -c $<  $( CFLAGS )

valgrind : chiffrer
	valgrind --leak-check = full ./chiffrer 000000

clean :
	rm -f *.o
	rm -f chiffrer