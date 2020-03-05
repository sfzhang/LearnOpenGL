all: oneface3d cube multicube
oneface3d: oneface3d.cpp
	g++ -g -o ../bin/oneface3d oneface3d.cpp -lglfw -lglad -lGL

cube: cube.cpp
	g++ -g -o ../bin/cube cube.cpp -lglfw -lglad -lGL

multicube: multicube.cpp
	g++ -g -o ../bin/multicube multicube.cpp -lglfw -lglad -lGL


.PHONY: clean
clean:
	rm -f ../bin/oneface3d
	rm -f ../bin/cube
	rm -f ../bin/multicube
