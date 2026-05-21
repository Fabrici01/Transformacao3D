#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "camera.h"

//Aloca a estrutura de mem�ria para representar a c�mera
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

//Recebe os par�metros espec�ficos da c�mera e calcula viewMatrix
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

	//Cálculo ViewMatrix;	
}

//Desaloca a c�mera
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
