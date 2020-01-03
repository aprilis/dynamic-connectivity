CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wshadow

SRC = $(wildcard *.cpp)
HD = $(wildcard *.h)

dc: $(SRC) $(HD)
	g++ $(CXXFLAGS) $(SRC) -o dc

clean:
	rm dc