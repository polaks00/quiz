#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "configuration.h"
#include "menu.h"


const int WIDTH =1920, HEIGHT = 1080;

int main( int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("quiz", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
            std::cerr << "Nie udało się utworzyć renderer'a: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

    TTF_Font* font = TTF_OpenFont("assets/font.ttf",32);
    
    Configuration configuration(window, renderer, "test.jpg");
    configuration.render();
    
    Menu menu(renderer,font);
    menu.render();

    SDL_Event windowEvent;
    int result = 0;
    
    while(true)
    {
        if(SDL_PollEvent(&windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
            break;
            result = menu.handleEvents(windowEvent);
            if(result)
            {
                SDL_HideWindow(window);
                printf("ez\n"); // zadzialalo klikniecie, trzeba terz pobrac liczbe zdjec
            }
            
        }
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_Quit();

    return 0;
}