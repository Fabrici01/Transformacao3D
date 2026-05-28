all: compila

compila: algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o
	gcc -I src/include -L src/lib algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o -o prog -lmingw32 -lSDL2main -lSDL2

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
	rm *.o prog

