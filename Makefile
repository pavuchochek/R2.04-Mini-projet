all:
	gcc -I include src/*.c  -o bin/main.out

clean:
	rm -v bin/*.out
