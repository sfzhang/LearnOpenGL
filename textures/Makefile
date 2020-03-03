all: texture mixtex fourfaces singlepexel keyctrltex
texture: texture.cpp
	g++ -g -o ../bin/texture texture.cpp -lglfw -lglad -lGL

mixtex: mixtex.cpp
	g++ -g -o ../bin/mixtex mixtex.cpp -lglfw -lglad -lGL

fourfaces: fourfaces.cpp
	g++ -g -o ../bin/fourfaces fourfaces.cpp -lglfw -lglad -lGL

singlepexel: singlepexel.cpp
	g++ -g -o ../bin/singlepexel singlepexel.cpp -lglfw -lglad -lGL

keyctrltex: keyctrltex.cpp
	g++ -g -o ../bin/keyctrltex keyctrltex.cpp -lglfw -lglad -lGL



.PHONY: clean
clean:
	rm -f ../bin/texture
	rm -f ../bin/mixtex
	rm -f ../bin/fourfaces
	rm -f ../bin/singlepexel
	rm -f ../bin/keyctrltex
