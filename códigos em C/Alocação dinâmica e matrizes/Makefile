all : prog 

run :
		./prog < input.txt

matrix.o : matrix.c
	gcc -o matrix.o -c matrix.c

main.o : main.c
	gcc -o main.o -c main.c

prog : matrix.o main.o
	gcc -o prog matrix.o main.o

clean :
	rm -f *.o
	rm -f prog		
