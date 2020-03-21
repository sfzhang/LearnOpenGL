all: lightingmaps specularmaps
lightingmaps: lightingmaps.cpp
	g++ -g -o ../bin/lightingmaps lightingmaps.cpp -lglfw -lglad -lGL

specularmaps: specularmaps.cpp
	g++ -g -o ../bin/specularmaps specularmaps.cpp -lglfw -lglad -lGL

.PHONY: clean
clean:
	rm -f ../bin/lightingmaps
	rm -f ../bin/specularmaps
