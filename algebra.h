#include <stdio.h>

//Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz);

//Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz);

//Multiplica uma matriz 4d por um ponto
void multMatriz4dPonto(float **matriz, float *ponto);

//Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB);

//Normaliza vetor 3D
void normalizarVetor3D(float* vetor);

//Produto Escalar 3D
double produtoEscalar3D(float* vetor1, float* vetor2);

//Produto vetorial
float* produtoVetorial3D(float* vetor1, float* vetor2);

//Subtrair vetores
float* subtracaoVetorial3D(float* vetor1, float* vetor2);
