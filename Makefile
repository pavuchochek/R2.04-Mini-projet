all:
	gcc -I include src/*.c  -o bin/main.out

gui:
	 gcc -I include src/gui.c src/chiffrement.c src/utils.c -o bin/gui.out `sdl2-config --cflags --libs` -lSDL2_ttf

clean:
	rm -v bin/*.out
