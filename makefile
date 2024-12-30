all: parafrase

parafrase: main.o arvores.o arquivos.o
	gcc -o parafrase main.o arvores.o arquivos.o

main.o: main.c arquivos.h arvores.h
	gcc -o main.o main.c -c -Wall

arvores.o: arvores.c arvores.h
	gcc -o arvores.o arvores.c -c -Wall

arquivos.o: arquivos.c arquivos.h
	gcc -o arquivos.o arquivos.c -c -Wall