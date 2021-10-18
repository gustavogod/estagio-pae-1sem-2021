all : prog

run : 
		./prog < teste.txt

sql.o : sql.c
		gcc -o sql.o -c sql.c

myString.o : myString.c
		gcc -o myString.o -c myString.c

sqlCommands.o : sqlCommands.c 
		gcc -o sqlCommands.o -c sqlCommands.c

table.o : table.c
		gcc -o table.o -c table.c

file.o : file.c 
		gcc -o file.o -c file.c		

prog: sql.o myString.o sqlCommands.o table.o file.o
		gcc -o prog sql.o myString.o sqlCommands.o table.o file.o