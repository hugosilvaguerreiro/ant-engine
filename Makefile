LIB_NAME = libantEngine.a

GCC	= g++
EXPORT=export
BIN	= $(EXPORT)/$(LIB_NAME)

OBJ = build
SRC = src

SOURCES =  libAntEngine.cpp
INCS	= -lsfml-graphics -lsfml-window -lsfml-system
LIBS	=

LINKOBJ	= $(SOURCES:.cpp=.o)

all: clean $(BIN)

$(BIN): $(LINKOBJ)
	ar crv $(BIN) $(OBJ)/$(LINKOBJ)
	cp libAntEngine.h $(EXPORT)

.cpp.o:
	$(GCC) -g -c $< -o $(OBJ)/$@ $(INCS) -std=c++0x

clean:
	rm -f $(OBJ)/$(LINKOBJ)
	rm -f $(BIN)
	rm -f $(EXPORT)/*.h

run: clean $(BIN)
	$(BIN)

install: $(BIN)
	sudo cp $(BIN) /usr/local/lib
	sudo cp $(EXPORT)/*.h /usr/local/include/

valgrind:
	valgrind --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         $(BIN)

