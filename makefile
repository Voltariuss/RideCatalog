CC=g++
DEBUG=false
CFLAGS=-Wall -ansi -pedantic -std=c++11
ifeq ($(DEBUG), true)
    CFLAGS+=-g -DMAP
endif
LDFLAGS=-g
SRC=Main.cpp Catalogue.cpp Collection.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp Persistance.cpp
OBJ=$(SRC:.cpp=.o)

voyage: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o
