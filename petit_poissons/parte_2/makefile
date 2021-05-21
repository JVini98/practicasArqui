default: all

all: poissons_2

poissons_2: poissons_2.c
	 gcc -Wall -o poissons_2 poissons_2.c -pthread

clean:
	rm -f *.o
	rm -f poissons_2

run: ./poissons_2
	./poissons_2
