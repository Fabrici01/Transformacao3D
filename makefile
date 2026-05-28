all: compila

compila: algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o
	gcc -I src/include algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o -o prog -lSDL2 -lm

algebra.o: algebra.c
	gcc -c algebra.c

camera.o: camera.c
	gcc -c camera.c -I src/include

colaTrabalho.o: colaTrabalho.c
	gcc -c colaTrabalho.c -I src/include

main.o: main.c
	gcc -c main.c -I src/include

objeto.o: objeto.c
	gcc -c objeto.c -I src/include

tela.o: tela.c
	gcc -c tela.c -I src/include
rm:
	rm -f *.o prog
	