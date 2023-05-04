all:
	gcc -I include src/*.c  -o bin/main.out

gui:
	 gcc src/gui.c -o build/gui `sdl2-config --cflags --libs` -lSDL2_ttf

clean:
	rm -v bin/*.out
