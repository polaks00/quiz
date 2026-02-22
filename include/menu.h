#ifndef MENU_H
#define MENU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "configuration.h"


struct UI_Button
{
    SDL_Rect rect;
    SDL_Color color;
    std::string text;
    SDL_Texture* textTexture;
};

class Menu {
private:
    SDL_Renderer* renderer;
    std::vector<UI_Button> buttons;
    void createButton(int x, int y, int w, int h, SDL_Color color, std::string text, TTF_Font* font);

public:
    Menu(SDL_Renderer* renderer_quiz, TTF_Font* font);
    ~Menu();
    void render();
    int handleEvents(SDL_Event& event);

private:
    bool isMouseOverButton(int mouseX, int mouseY, const SDL_Rect& buttonRect);
};

#endif