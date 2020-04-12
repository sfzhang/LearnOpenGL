all: dirlight pointlight spotlight
dirlight: dirlight.cpp
	g++ -g -o ../bin/dirlight dirlight.cpp -lglfw -lglad -lGL

pointlight: pointlight.cpp
	g++ -g -o ../bin/pointlight pointlight.cpp -lglfw -lglad -lGL

spotlight: spotlight.cpp
	g++ -g -o ../bin/spotlight spotlight.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/dirlight
	rm -f ../bin/pointlight
	rm -f ../bin/spotlight
