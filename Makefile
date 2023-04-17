all:
	gcc -I include src/main.c  -o bin/main.out


clean:
	rm -v bin/*.out
