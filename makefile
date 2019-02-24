build:
	gcc -Wall -g main.c -o main

run:
	./main

clean:
	rm -f *.o *~ main
