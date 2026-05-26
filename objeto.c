#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"

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
        obj->arestas[i] = (int*)malloc(obj->nArestas * sizeof(int));
        fscanf(f, "%d", &obj->arestas[i][0]);
        fscanf(f, "%d", &obj->arestas[i][1]);
    }

    //Falta ModelMatrix, Transl, Escala, Rx, Ry e Rz

    return obj;
}

//Altera a modelMatrix de um objeto para redimenciona-lo segundo os parametros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ){

}

//Altera a modelMatrix de um objeto para translada-lo segundo os par�metros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo informado
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo){

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

    free(objeto->pontos);
    free(objeto->arestas);

    //Faltam as outras 

    free(objeto);
}

