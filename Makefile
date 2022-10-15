all: main

main: src/*.cpp
	g++ --std=c++14 -O3 -Wall -Werror -pedantic -fpermissive src/*.cpp -o pdi

debug: src/*.cpp
	g++ --std=c++14 -g -Wall -Werror -pedantic -fpermissive src/*.cpp -o pdi

.PHONY:
	clean

clean:
	rm -rf *~ pdi