#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "algebra.h"

//Le as informacoes de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(char *nomeArquivo){
    tObjeto3d *obj = malloc(sizeof(tObjeto3d));
    FILE *f = fopen(nomeArquivo, "r");

    if(f == NULL){
    	printf("\nArquivo nao encontrado!!\n");
	exit(1);
    }

    fscanf(f, "%d", &obj->nPontos);
    obj->pontos = (float**)malloc(obj->nPontos * sizeof(float*));

    for(int i = 0; i < obj->nPontos; i++){
    	obj->pontos[i] = (float*)malloc(3 * sizeof(float));
	    fscanf(f, "%f", &obj->pontos[i][0]);
    	fscanf(f, "%f", &obj->pontos[i][1]);
	    fscanf(f, "%f", &obj->pontos[i][2]);
    }

    fscanf(f, "%d", &obj->nArestas);
    obj->arestas = (int**)malloc(obj->nArestas * sizeof(int*));

    for(int i = 0; i < obj->nArestas; i++){
        obj->arestas[i] = (int*)malloc(2 * sizeof(int));
        fscanf(f, "%d", &obj->arestas[i][0]);
        fscanf(f, "%d", &obj->arestas[i][1]);
    }

    obj->transl = (float*) calloc(3, sizeof(float));

    obj->escala = (float*) calloc(3, sizeof(float));
    for(int x=0; x<3; x++)obj->escala[x] = 1.0;

    obj->Rx = 0.0;
    obj->Ry = 0.0;
    obj->Rz = 0.0;


    criaIdentidade4d(obj->modelMatrix);
    
    //Falta ModelMatrix, Transl, Escala, Rx, Ry e Rz

    fclose(f);
    return obj;
}

//Altera a modelMatrix de um objeto para redimenciona-lo segundo os parametros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ){
    //Cria uma matriz 4x4 com 0's
    float** matriz = (float**) calloc(4,sizeof(float*));
    for(int x=0; x<4; x++){
        matriz[x] = (float*) calloc(4, sizeof(float));
    }

    //Insere dados na matriz
    matriz[0][0] = escalaX;
    matriz[1][1] = escalaY;
    matriz[2][2] = escalaZ;
    matriz[3][3] = 1;

    //Realiza a multiplicação
    multMatriz4d(matriz, objeto->modelMatrix);

    //Libera memória
    for(int x=0; x<4; x++){
        free(matriz[x]);
    }
    free(matriz);
}

//Altera a modelMatrix de um objeto para translada-lo segundo os par�metros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ){
    //Cria uma matriz 4x4 com 0's
    float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++){
        matriz[x] = (float*) calloc(4, sizeof(float));
    }

    //Insere dados na matriz
    matriz[0][0] = 1;
    matriz[1][1] = 1;
    matriz[2][2] = 1;
    matriz[3][3] = 1;
    matriz[0][3] = transX;
    matriz[1][3] = transY;
    matriz[2][3] = transZ;

    //Realiza a multiplicação
    multMatriz4d(matriz, objeto->modelMatrix);    

    //Libera memória
    for(int x=0; x<4; x++){
        free(matriz[x]);
    }
    free(matriz);
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo  (Passar angulo em graus)
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo){
    float radiano = angulo * (M_PI / 180.0);

    //Cria uma matriz 4x4 com 0's
    float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++){
        matriz[x] = (float*) calloc(4, sizeof(float));
    }

    //Insere dados na matriz
    matriz[0][0] = 1;
    matriz[1][1] = cos(radiano);
    matriz[1][2] = -1.0 * sin(radiano);
    matriz[2][1] = sin(radiano);
    matriz[2][2] = cos(radiano);
    matriz[3][3] = 1;

    //Realiza a multiplicação
    multMatriz4d(matriz, objeto->modelMatrix);    

    //Libera memória
    for(int x=0; x<4; x++){
        free(matriz[x]);
    }
    free(matriz);
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo){
    float radiano = angulo * (M_PI / 180.0);

    //Cria uma matriz 4x4 com 0's
    float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++){
        matriz[x] = (float*) calloc(4, sizeof(float));
    }

    //Insere dados na matriz
    matriz[0][0] = cos(radiano);
    matriz[0][2] = sin(radiano);
    matriz[1][1] = 1;
    matriz[2][0] = -1.0 * sin(radiano);
    matriz[2][2] = cos(radiano);
    matriz[3][3] = 1;

    //Realiza a multiplicação
    multMatriz4d(matriz, objeto->modelMatrix);    

    //Libera memória
    for(int x=0; x<4; x++){
        free(matriz[x]);
    }
    free(matriz);
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo){
    float radiano = angulo * (M_PI / 180.0);

    //Cria uma matriz 4x4 com 0's
    float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++){
        matriz[x] = (float*) calloc(4, sizeof(float));
    }

    //Insere dados na matriz
    matriz[0][0] = cos(radiano);
    matriz[0][1] = -1.0 * sin(radiano);
    matriz[1][0] = sin(radiano);
    matriz[1][1] = cos(radiano);
    matriz[2][2] = 1;
    matriz[3][3] = 1;

    //Realiza a multiplicação
    multMatriz4d(matriz, objeto->modelMatrix);    

    //Libera memória
    for(int x=0; x<4; x++){
        free(matriz[x]);
    }
    free(matriz);
}

//Imprime um objeto no terminal
void imprimeObjetoDBG(tObjeto3d *objeto){
    //Usando para testar a leitura
    printf("\n%d\n", objeto->nPontos);
    for(int i = 0; i < objeto->nPontos; i++){
        for(int j = 0; j < 3; j++){
            printf("%f ", objeto->pontos[i][j]);
        }
        printf("\n");
    }

    printf("\n%d\n", objeto->nArestas);
    for(int i = 0; i < objeto->nArestas; i++){
        for(int j = 0; j < 2; j++){
            printf("%d ", objeto->arestas[i][j]);
        }
        printf("\n");
    }
}

//Desaloca o objeto
void desalocaObjeto(tObjeto3d *objeto){
    for(int i = 0; i < objeto->nPontos; i++){
        free(objeto->pontos[i]);
    }

    for(int i = 0; i < objeto->nArestas; i++){
        free(objeto->arestas[i]);
    }

    for(int i = 0; i < 4; i++){
        free(objeto->modelMatrix[i]);
    }
    free(objeto->modelMatrix);

    free(objeto->pontos);
    free(objeto->arestas);
    free(objeto->transl);
    free(objeto->escala);

    //Faltam as outras 

    free(objeto);
}

