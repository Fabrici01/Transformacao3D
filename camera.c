#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "camera.h"
#include "algebra.h"

//Aloca a estrutura de memoria para representar a cemera
tCamera3d *criaCamera(){

    tCamera3d *camera = (tCamera3d *)malloc(sizeof(tCamera3d));
    if(camera == NULL){
        printf("Erro ao criar camera\n");
        return NULL;
    }

    // Multiplica-se por 3, pois se trata de 3 dimensões
    camera->posicao = (float*)malloc(sizeof(float)*3);
    camera->foco = (float*)malloc(sizeof(float)*3);
    camera->cima = (float*)malloc(sizeof(float)*3);

    //Agora são 4 dimensões, (x, y,z, w);
    camera->viewMatrix = (float**)malloc(sizeof(float*)*4);
    for(int i = 0; i < 4; i++){
    	camera->viewMatrix[i] = (float*)malloc(sizeof(float)*4);
    }

    return camera;
}

//Recebe os parametros especificos da camera e calcula viewMatrix
void defineCamera(tCamera3d *camera, float posX, float posY, float posZ, float focX, float focY, float focZ, float cimX, float cimY, float cimZ){
	camera->posicao[0] = posX;
	camera->posicao[1] = posY;
	camera->posicao[2] = posZ;

	camera->foco[0] = focX;
	camera->foco[1] = focY;
	camera->foco[2] = focZ;

	camera->cima[0] = cimX;
	camera->cima[1] = cimY;
	camera->cima[2] = cimZ;

	//Não sei se está correto
	float* n = subtracaoVetorial3D(camera->posicao,camera->foco);
	normalizarVetor3D(n);

	float* u = produtoVetorial3D(camera->cima, n);
	normalizarVetor3D(u);

	float* v = produtoVetorial3D(n, u);
	normalizarVetor3D(v);

	camera->viewMatrix[0][0] = u[0];
	camera->viewMatrix[0][1] = u[1];
	camera->viewMatrix[0][2] = u[2];
	camera->viewMatrix[0][3] = -1.0 * produtoEscalar3D(u, camera->posicao);

	camera->viewMatrix[1][0] = v[0];
	camera->viewMatrix[1][1] = v[1];
	camera->viewMatrix[1][2] = v[2];
	camera->viewMatrix[1][3] = -1.0 * produtoEscalar3D(v, camera->posicao);

	camera->viewMatrix[2][0] = n[0];
	camera->viewMatrix[2][1] = n[1];
	camera->viewMatrix[2][2] = n[2];
	camera->viewMatrix[2][3] = -1.0 * produtoEscalar3D(n, camera->posicao);

	camera->viewMatrix[3][0] = 0;
	camera->viewMatrix[3][1] = 0;
	camera->viewMatrix[3][2] = 0;
	camera->viewMatrix[3][3] = 1;

	free(u);
	free(n);
	free(v);
	//Criação de matrizes usando criaIdentidade4d;
}

//Desaloca a camera
void desalocaCamera(tCamera3d *objeto){
	for(int i = 0; i < 4; i++){
		free(objeto->viewMatrix[i]);
	}

	free(objeto->viewMatrix);
	free(objeto->cima);
	free(objeto->foco);
	free(objeto->posicao);
	free(objeto);
}