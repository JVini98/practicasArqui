default: all

all: poissons_3

poissons_3: poissons_3.c
	 gcc -Wall -o poissons_3 poissons_3.c -pthread

clean:
	rm -f *.o
	rm -f poissons_3

run: ./poissons_3
	./poissons_3         
