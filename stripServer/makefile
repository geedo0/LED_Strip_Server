all: stripServer

stripServer: main.o
	gcc main.o -o stripServer -lwiringPi

main.o: main.c
	gcc -c main.c
	
clean:
	rm -rf *.o stripServer *~
