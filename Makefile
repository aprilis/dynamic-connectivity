CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wshadow -fsanitize=address -fsanitize=undefined -static-libasan

SRC = forest.cpp treap.cpp main.cpp
#$(wildcard *.cpp)
HD = $(wildcard *.h)

dc: $(SRC) $(HD)
	g++ $(CXXFLAGS) $(SRC) -o dc

check: 
	g++ $(CXXFLAGS) brute.cpp -o brute
	g++ $(CXXFLAGS) gen.cpp -o gen

clean:
	rm dc
	rm brute