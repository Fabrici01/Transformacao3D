#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"
#include "tela.h"
#include "algebra.h"
#include "camera.h"

//Cria Matriz Ortogonal de projeção
float** criarProjMartrixOrtogonal(float left, float right, float bottom, float top, float near, float far);

//Cria Matriz Perspectiva de projeção
float** criarProjMartrixPerspectiva(float left, float right, float bottom, float top, float near, float far);


//desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto){

}


int main( int argc, char * argv[] ){
    int x1, x2;
    int y1, y2;
    tObjeto3d *obj = carregaObjeto("cubo.dcg");
    tCamera3d *cam = criaCamera();
    defineCamera(cam, 20, 15, 25, 0, 0, 6, 0, 1, 0);


    if (SDL_Init( SDL_INIT_EVERYTHING) < 0){
        printf("SDL nao inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("Hello SDL World!");

    if(window == NULL){
        printf("SDL nao criou a janela! SDL Erro: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event windowEvent;

    while(1){
        if( SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT){
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //ESCREVA AQUI O SEU PROGRAMA
        

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        SDL_RenderPresent(renderer);
    }

    desalocaTela(window);
    SDL_Quit();

    imprimeObjetoDBG(obj);

    return EXIT_SUCCESS;
}

float** criarProjMartrixOrtogonal(float left, float right, float bottom, float top, float near, float far){
	float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++) matriz[x] = (float*) calloc(4, sizeof(float));

    matriz[0][0] = 2.0 / (right - left);
    matriz[0][3] = -(right + left) / (right - left);

    matriz[1][1] = 2.0 / (top - bottom);
    matriz[1][3] = -(top + bottom) / (top - bottom);

    matriz[2][2] = -2 / (far - near);
    matriz[2][3] = -(far + near) / (far - near);

    matriz[3][3] = 1;

    return matriz;
}

float** criarProjMartrixPerspectiva(float left, float right, float bottom, float top, float near, float far){
	float** matriz = (float**) calloc(4, sizeof(float*));
    for(int x=0; x<4; x++) matriz[x] = (float*) calloc(4, sizeof(float));

    matriz[0][0] = (2 * near) / (right - left);
    matriz[0][2] = (right + left) / (right - left);

    matriz[1][1] = (2 * near) / (top - bottom);
    matriz[1][2] = (top + bottom) / (top - bottom);

    matriz[2][2] = -(far + near) / (far - near);
    matriz[2][3] = -2 * (far * near) / (far - near);

    matriz[3][2] = -1;

    return matriz;
}
