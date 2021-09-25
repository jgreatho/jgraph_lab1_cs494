EXECUTABLES = bin/pegsol bin/peg2jgraph

CFLAGS ?= -Wall -Wextra -std=c++98

all: $(EXECUTABLES)

clean:
	rm -f a.out bin/*

bin/pegsol: src/pegsol.cpp
	g++ $(CFLAGS) -o bin/pegsol src/pegsol.cpp

bin/peg2jgraph: src/peg2jgraph.cpp
	g++ $(CFLAGS) -o bin/peg2jgraph src/peg2jgraph.cpp
