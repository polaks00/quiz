#ifndef MENU_H
#define MENU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "configuration.h"

namespace fs = std::filesystem;

class QuizEngine;

enum class GameState {
    MAIN_MENU,
    CATEGORY_SELECT,
    QUIZ_ACTIVE
};

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
    SDL_Texture* titleTexture;
    SDL_Rect titleRect;
    std::vector<UI_Button> mainButtons;
    std::vector<UI_Button> categoryButtons;
    void createButton(std::vector<UI_Button> &button_localization, int x, int y, int w, int h, SDL_Color color, std::string text, TTF_Font* font);

public:
    Menu(SDL_Renderer* renderer_quiz, TTF_Font* font, TTF_Font* title_font);
    ~Menu();
    void render(GameState currentState); 
    int handleEvents(SDL_Event& event, GameState& currentState, QuizEngine* quiz);
    std::vector<std::string> getCategoriesFromData();

private:
    bool isMouseOverButton(int mouseX, int mouseY, const SDL_Rect& buttonRect);
};

#endif