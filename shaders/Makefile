all: shader1 uniform vbo_color
shader1: shader1.cpp
	g++ -g -o ../bin/shader1 shader1.cpp -lglfw -lglad -lGL

uniform: uniform.cpp
	g++ -g -o ../bin/uniform uniform.cpp -lglfw -lglad -lGL

vbo_color: vbo_color.cpp
	g++ -g -o ../bin/vbo_color vbo_color.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/shader1
	rm -f ../bin/uniform
	rm -f ../bin/vbo_color
