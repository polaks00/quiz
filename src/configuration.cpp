#include "configuration.h"


    Configuration::Configuration(SDL_Renderer* renderer_quiz) 
        : renderer(renderer_quiz)
    {

    }

    Configuration::~Configuration() 
    {

    }

    void Configuration::render() 
    {
        
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_RenderFillRect(renderer, NULL);
        
    }

    




