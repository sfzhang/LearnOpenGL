all: triangle_vbo triangle_vao triangle_ebo triangle_vao2 triangle_frag

triangle_vbo: triangle_vbo.cpp
	g++ -g -o ../bin/triangle_vbo triangle_vbo.cpp -lglfw -lglad -lGL

triangle_vao: triangle_vao.cpp
	g++ -g -o ../bin/triangle_vao triangle_vao.cpp -lglfw -lglad -lGL

triangle_vao2: triangle_vao2.cpp
	g++ -g -o ../bin/triangle_vao2 triangle_vao2.cpp -lglfw -lglad -lGL

triangle_ebo: triangle_ebo.cpp
	g++ -g -o ../bin/triangle_ebo triangle_ebo.cpp -lglfw -lglad -lGL

triangle_frag: triangle_frag.cpp
	g++ -g -o ../bin/triangle_frag triangle_frag.cpp -lglfw -lglad -lGL



.PHONY: clean
clean:
	rm -f ../bin/triangle_vbo
	rm -f ../bin/triangle_vao
	rm -f ../bin/triangle_vao2
	rm -f ../bin/triangle_ebo
	rm -f ../bin/triangle_frag
