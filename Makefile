CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow

SRC = forest.cpp treap.cpp main.cpp
#$(wildcard *.cpp)
HD = $(wildcard *.h)

dc: $(SRC) $(HD)
	g++ $(CXXFLAGS) $(SRC) -o dc

check: 
	g++ $(CXXFLAGS) brute.cpp -o brute
	g++ $(CXXFLAGS) gen.cpp -o gen

debug: $(SRC) $(HD)
	g++ $(CXXFLAGS) $(SRC) -g -o dc-debug

all: dc check debug

clean:
	rm dc dc-debug brute