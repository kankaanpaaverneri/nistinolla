CC = g++
CFLAGS = -c -std=c++17 -g -Wall
objects = main.o Pelaajat.o Pelaaja.o \
		Tietokone.o Util.o Grid.o

all: compile clean

compile: ${objects}
	${CC} ${objects} -o nistinolla

main.o: main.cpp
	${CC} ${CFLAGS} main.cpp

Pelaajat.o: Pelaajat.cpp Pelaajat.h
	${CC} ${CFLAGS} Pelaajat.cpp Pelaajat.h

Pelaaja.o: Pelaaja.cpp Pelaaja.h
	${CC} ${CFLAGS} Pelaaja.cpp Pelaaja.h

Tietokone.o: Tietokone.cpp Tietokone.h
	${CC} ${CFLAGS} Tietokone.cpp Tietokone.h

Util.o: Util.h Util.cpp
	${CC} ${CFLAGS} Util.cpp Util.h

Grid.o: Grid.h Grid.cpp
	${CC} ${CFLAGS} Grid.h Grid.cpp

clean:
	rm ${objects} *.gch