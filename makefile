all:
	g++ -Isrc/Include -Isrc/function -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer