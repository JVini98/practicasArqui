default: all

all: poissons_1

poissons_1: poissons_1.c
	 gcc -Wall -o poissons_1 poissons_1.c -pthread

clean:
	rm -f *.o
	rm -f poissons_1

run: ./poissons_1
	./poissons_1
