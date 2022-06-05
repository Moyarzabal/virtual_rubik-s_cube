rubik_cube: rubik_cube.cpp
	g++ -o rubik_cube rubik_cube.cpp $(pkg-config opencv --cflags --libs) $(pkg-config gl --cflags --libs) $(pkg-config glu --cflags --libs) -lglut
