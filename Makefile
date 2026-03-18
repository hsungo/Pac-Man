SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

run: pacman
	./pacman

pacman: $(OBJS)
	g++ -Wall -Iinclude -o $@ $^

%.o: %.cpp
	g++ -Wall -Iinclude -c $< -o $@

clean:
	rm -f $(OBJS) pacman
	clear