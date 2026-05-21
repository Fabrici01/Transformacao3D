all: compila

compila: algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o
	gcc algebra.o camera.o colaTrabalho.o main.o objeto.o tela.o -o prog -L/home/raphael/Downloads/Instaladores/SLD-2.32.10/build-scripts -lSDL2

algebra.o: algebra.c
	gcc -c algebra.c

camera.o: camera.c
	gcc -c camera.c

colaTrabalho.o: colaTrabalho.c
	gcc -c colaTrabalho.c

main.o: main.c
	gcc -c main.c

objeto.o: objeto.c
	gcc -c objeto.c

tela.o: tela.c
	gcc -c tela.c
rm:
	rm *.o prog

