
all : prog

run : 
		./prog < in.txt

robot.o : robot.c
		gcc -o robot.o -c robot.c

map.o : map.c
		gcc -o map.o -c map.c

prog : robot.o map.o
		gcc -o prog robot.o map.o

clean : 
	rm -f *.o
	rm -f prog