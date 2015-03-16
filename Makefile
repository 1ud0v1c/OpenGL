CC=g++
CFLAGS=-W -Wall -pedantic -std=c++11 -g
LDFLAGS=-lm
SRC=src
INC=-I inc/
EXEC=main

all: $(EXEC)

main: $(SRC)/main.cpp vertex.o
	$(CC) $(INC) -o $(SRC)/$@ $^ $(CFLAGS) $(LDFLAGS)

%.o: $(SRC)/%.cpp
	$(CC) $(INC) -o $@ -c $< $(CFLAGS) 

clean:
	rm *.o
