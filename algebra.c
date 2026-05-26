#include <stdio.h>

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

}

//Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto){

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
