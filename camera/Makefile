all: lookat wasd mousecam
lookat: lookat.cpp
	g++ -g -o ../bin/lookat lookat.cpp -lglfw -lglad -lGL

wasd: wasd.cpp
	g++ -g -o ../bin/wasd wasd.cpp -lglfw -lglad -lGL

mousecam: mousecam.cpp
	g++ -g -o ../bin/mousecam mousecam.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/lookat
	rm -f ../bin/wasd
	rm -f ../bin/mousecam
