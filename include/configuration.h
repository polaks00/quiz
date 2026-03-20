#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Configuration {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    


public:
    Configuration(SDL_Renderer* renderer_quiz);
    ~Configuration();
    void render();

private:
    
};

#endif