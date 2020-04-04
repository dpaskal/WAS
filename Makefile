FLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic

all: was

was: main.cpp
	g++ main.cpp -o was $(FLAGS)

clean:
	rm -f was