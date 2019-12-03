CCPP=g++
DEBUG=true
CPPFLAGS=-Wall -g -ansi -pedantic -std=c++11
ifeq (DEBUG, true)
    CPPFLAGS+=-DMAP
endif
LDFLAGS=-g
SRC=Main.cpp Catalogue.cpp Collection.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp Persistance.cpp
OBJ=$(SRC:.cpp=.o)

voyage: $(OBJ)
	$(CCPP) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CCPP) -o $@ -c $< $(CPPFLAGS)

clean:
	rm *.o
