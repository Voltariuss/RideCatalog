CCPP=g++
CPPFLAGS=-Werror -Wall -DMAP
LDFLAGS=
EXEC=voyage
SRC=Main.cpp Catalogue.cpp Collection.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CCPP) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CCPP) -o $@ -c $< $(CPPFLAGS)

clean:
	rm -rf *.o