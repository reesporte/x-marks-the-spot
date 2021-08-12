LDFLAGS=-lncurses

all: game

game: main.c 
	cc main.c -o game $(LDFLAGS)

run: game 
	./game

clean: 
	rm game 

install: game
	cp game /usr/local/bin
