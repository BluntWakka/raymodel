CFLAGS=`pkg-config --cflags sdl2`
LFLAGS=`pkg-config --libs sdl2`

raymodel: 
	g++ raymodel.cpp ${CFLAGS} -o raymodel ${LFLAGS}
clean:
	rm -f *.o
	rm -f raymodel