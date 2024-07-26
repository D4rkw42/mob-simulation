#include <SDL2/SDL.h>
#define SDL_MAIN_HANDLED

int main(int argc, char* argv[]) {
   SDL_Window* window = NULL;

    /*
     * Inicialização e criação da janela
     */
    if ( SDL_Init(SDL_INIT_VIDEO) == 0 )
        window = SDL_CreateWindow("Tutorial SDL 2", 50, 50, 640, 480, 0);
    else
        SDL_Log("Erro na inicialização: %s", SDL_GetError());

    /*
     * Main loop
     */
    if ( window != NULL )
        while( !SDL_QuitRequested() ) { /* ... */ }
    else
        SDL_Log("Erro na criação da janela: %s", SDL_GetError());

    /*
     * Finialização
     */
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}