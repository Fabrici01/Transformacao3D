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
void desenhaObjetoTela(SDL_Renderer *renderer, float **matrizProjecao, tCamera3d *camera, tObjeto3d *objeto);


int main( int argc, char * argv[] ){
    tObjeto3d *obj = carregaObjeto("cubo.dcg");
    tCamera3d *cam = criaCamera();
    defineCamera(cam, 20, 15, 25, 0, 0, 6, 0, 1, 0);

    float** matrizProj = criarProjMartrixOrtogonal(-16, 16, -12, 12, 1, 50);


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
        if(SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT){
                break;
            }
            if(windowEvent.type == SDL_KEYDOWN){
                switch(windowEvent.key.keysym.sym){
                    // Translação
                    case SDLK_w: transladaObjeto(obj,  0,  1,  0); break;
                    case SDLK_s: transladaObjeto(obj,  0, -1,  0); break;
                    case SDLK_a: transladaObjeto(obj, -1,  0,  0); break;
                    case SDLK_d: transladaObjeto(obj,  1,  0,  0); break;
                    case SDLK_q: transladaObjeto(obj,  0,  0,  1); break;
                    case SDLK_e: transladaObjeto(obj,  0,  0, -1); break;
                    // Rotação
                    case SDLK_UP:    rotacionaObjetoEixoX(obj,  5); break;
                    case SDLK_DOWN:  rotacionaObjetoEixoX(obj, -5); break;
                    case SDLK_LEFT:  rotacionaObjetoEixoY(obj,  5); break;
                    case SDLK_RIGHT: rotacionaObjetoEixoY(obj, -5); break;
                    case SDLK_z:     rotacionaObjetoEixoZ(obj,  5); break;
                    case SDLK_x:     rotacionaObjetoEixoZ(obj, -5); break;
                    // Escala
                    case SDLK_PLUS:
                    case SDLK_KP_PLUS: escalaObjeto(obj, 1.1f, 1.1f, 1.1f); break;
                    case SDLK_MINUS:
                    case SDLK_KP_MINUS: escalaObjeto(obj, 0.9f, 0.9f, 0.9f); break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        desenhaObjetoTela(renderer, matrizProj, cam, obj);
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

void desenhaObjetoTela(SDL_Renderer *renderer, float **matrizProjecao, tCamera3d *camera, tObjeto3d *objeto){
    float ponto[4];
    float **matrizPontos = (float**) malloc(objeto->nPontos * sizeof(float*));
    //SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    //Copia matriz de pontos do objeto para matrizPontos
    for(int x=0; x<objeto->nPontos; x++){
        matrizPontos[x] = (float*) malloc(4 * sizeof(float));
        matrizPontos[x][0] = objeto->pontos[x][0];
        matrizPontos[x][1] = objeto->pontos[x][1];
        matrizPontos[x][2] = objeto->pontos[x][2];
        matrizPontos[x][3] = objeto->pontos[x][3];
    }
    
    for(int x=0; x<objeto->nPontos; x++){
        for(int y=0; y<4; y++) ponto[y] = objeto->pontos[x][y];

        multMatriz4dPonto(objeto->modelMatrix, ponto);
        multMatriz4dPonto(camera->viewMatrix, ponto);
        multMatriz4dPonto(matrizProjecao, ponto);

        for(int y=0; y<4; y++) matrizPontos[x][y] = ponto[y];
    }

    for (int i = 0; i < objeto->nArestas; i++) {
        int v1 = objeto->arestas[i][0];
        int v2 = objeto->arestas[i][1];

        float w1 = matrizPontos[v1][3];
        float w2 = matrizPontos[v2][3];

        int x1 = (int)((matrizPontos[v1][0] / w1 + 1.0f) * WIDTH  / 2.0f);
        int y1 = (int)((1.0f - matrizPontos[v1][1] / w1) * HEIGHT / 2.0f);
        int x2 = (int)((matrizPontos[v2][0] / w2 + 1.0f) * WIDTH  / 2.0f);
        int y2 = (int)((1.0f - matrizPontos[v2][1] / w2) * HEIGHT / 2.0f);

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    for (int i = 0; i < objeto->nPontos; i++) free(matrizPontos[i]);
    free(matrizPontos);
}
