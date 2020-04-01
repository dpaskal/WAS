all: was

was: main.cpp
	g++ main.cpp -o was $(FLAGS)

clean:
	rm -f main