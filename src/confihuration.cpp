#include "configuration.h"


    Configuration::Configuration(SDL_Window* window_quiz, SDL_Renderer* renderer_quiz, const std::string& backgroundPath) 
        : window(window_quiz), renderer(renderer_quiz), backgroundTexture(nullptr)
    {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);



        // Ładowanie tekstur
        backgroundTexture = loadTexture(backgroundPath);
    }

    Configuration::~Configuration() 
    {
        // Czyszczenie zasobów
        SDL_DestroyTexture(backgroundTexture);
        IMG_Quit();
    }

    void Configuration::render() 
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_Texture* Configuration::loadTexture(const std::string& path) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Nie udało się załadować obrazu: " << IMG_GetError() << std::endl;
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }




