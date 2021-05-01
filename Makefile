LIB_NAME = libantEngine.a

GCC	= g++
EXPORT=export
BIN	= $(EXPORT)/$(LIB_NAME)

OBJ = build
SRC = src

SOURCES = $(shell find $(SRC) -name *.cpp)
HEADERS = $(shell find $(SRC) -name *.h)
#INCS	= -lsfml-graphics -lsfml-window -lsfml-system
INCS    = -lncurses
LIBS	= /usr/lib/libncurses.a -ldl

LINKOBJ	= $(SOURCES:.cpp=.o)

all: $(BIN)

$(BIN): $(LINKOBJ)
	ar crv $(BIN) $(LINKOBJ)

.cpp.o:
	$(GCC) -g -c $< -o $@ $(INCS) -std=c++0x

clean:
	rm -f $(LINKOBJ)
	rm -f $(BIN)
	rm -f $(EXPORT)/*.h

run: clean $(BIN)
	$(BIN)

install: $(BIN)
	sudo cp $(BIN) /usr/local/lib
	rsync -a --include '*/' --include '*.h' --exclude '*' src/ export/AntEngine
	sudo cp -r $(EXPORT)/AntEngine /usr/local/include/

valgrind:
	valgrind --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         $(BIN)

