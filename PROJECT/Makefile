#WordCount : 
#	g++ main.cpp Counter.cpp -I. -o P1
CC = g++
CFLAGS = -Wall -c		#compiler flags
LFLAGS = -Wall			#linkflags
OBJS = main.o Cipher.o
INCLUDE = -I.
P1 : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o Cipher

main.o :main.cpp Cipher.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

Cipher.o : Cipher.cpp Cipher.h
	$(CC) Cipher.cpp $(INCLUDE) $(CFLAGS)

clean :
	-rm *.o Cipher
