all: multilights
multilights: multilights.cpp
	g++ -g -o ../bin/multilights multilights.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/multilights
