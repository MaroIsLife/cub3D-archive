build:
	gcc -std=c99 main2.c -lSDL2 -o raycast;

run:
	./raycast;

clean:
	rm raycast;
