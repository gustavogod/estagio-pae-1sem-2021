
all : prog

run :
		./prog < input.txt

prog : jogo.o main.o
		gcc -o prog jogo.o main.o

jogo.o : jogo.c
		gcc -o jogo.o -c jogo.c

main.o : main.c
		gcc -o main.o -c main.c

clean : 
		rm -f *.o
		rm -f prog		
