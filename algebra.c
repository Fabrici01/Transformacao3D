#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i==j)
            {
                novaMatriz[i][j] = 1;
            }
            else
            {
                novaMatriz[i][j] = 0;
            }
        }
    }
}

//Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz){
    printf("\n===============IMPRIMINDO MATRIZ===============\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

//Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto){
    float *resultado = (float*)calloc(4, sizeof(float));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultado[i] += matriz[i][j] * ponto[j];
        }
    }
    return resultado;
}

//Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB){
    float  matrizTemp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrizTemp[i][j] = matrizB[i][j];
            matrizB[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                matrizB[i][j] += matrizA[i][k] * matrizTemp[k][j];
            }
        }
    }
}

void normalizarVetor3D(float* vetor){
    float soma = 0.0;

    for(int x=0; x<3; x++){
        soma += vetor[x] * vetor[x];
    }

    float tamanho = sqrt(soma);

    if(tamanho!=0){
        for(int x=0; x<3; x++){
            vetor[x] /= tamanho;
        }
    }
}

double produtoEscalar3D(float* vetor1, float* vetor2){
    double resultado = 0.0;

    for(int x=0; x<3; x++){
        resultado += vetor1[x] * vetor2[x];
    }

    return resultado;
}


float* produtoVetorial3D(float* vetor1, float* vetor2){
    float* resultado = (float*) malloc(3 * sizeof(float));

    resultado[0] = (vetor1[1] * vetor2[2]) - (vetor1[2] * vetor2[1]);
    resultado[1] = (vetor1[2] * vetor2[0]) - (vetor1[0] * vetor2[2]);
    resultado[2] = (vetor1[0] * vetor2[1]) - (vetor1[1] * vetor2[0]);

    return resultado;
}

float* subtracaoVetorial3D(float* vetor1, float* vetor2){
    float* resultado = (float*) malloc(3 * sizeof(float));

    resultado[0] = vetor1[0] - vetor2[0];
    resultado[1] = vetor1[1] - vetor2[1];
    resultado[2] = vetor1[2] - vetor2[2];
    
    return resultado;
}


