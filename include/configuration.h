#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Configuration {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;


public:
    Configuration(SDL_Window* window_quiz, SDL_Renderer* renderer_quiz, 
                  const std::string& backgroundPath);
    ~Configuration();
    void render();

private:
    SDL_Texture* loadTexture(const std::string& path);
};

#endif