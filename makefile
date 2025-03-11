CFLAGS=-g -Wall -Wextra -Wwrite-strings
LFLAGS=-g

raymodel: raymodel.o
	g++ ${LFLAGS} -o raymodel raymodel.o
raymodel.o: raymodel.cpp raymodel.h 
	g++ ${CFLAGS} -c raymodel.cpp
clean:
	rm -f *.o
	rm -f raymodel