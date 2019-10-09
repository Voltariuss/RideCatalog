CCPP=g++
CPPFLAGS=-Wall -g -ansi -pedantic -std=c++11 -DMAP
LDFLAGS=-g
SRC=Main.cpp Catalogue.cpp Collection.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp
OBJ=$(SRC:.cpp=.o)

voyage: $(OBJ)
	$(CCPP) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CCPP) -o $@ -c $< $(CPPFLAGS)

clean:
	rm -rf *.o
