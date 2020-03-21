all: ambient diffuse specular
ambient: ambient.cpp
	g++ -g -o ../bin/ambient ambient.cpp -lglfw -lglad -lGL

diffuse: diffuse.cpp
	g++ -g -o ../bin/diffuse diffuse.cpp -lglfw -lglad -lGL

specular: specular.cpp
	g++ -g -o ../bin/specular specular.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/ambient
	rm -f ../bin/diffuse
	rm -f ../bin/specular
