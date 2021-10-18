all : prog

run :
		./prog < in.txt

dates.o: dates.c
		gcc -o dates.o -c dates.c

ex72.o: ex72-ler-datas.c
		gcc -o ex72.o -c ex72-ler-datas.c

prog: dates.o ex72.o
		gcc -o prog ex72.o dates.o				