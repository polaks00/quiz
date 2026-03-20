#ifndef QUIZ_H
#define QUIZ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <filesystem>
#include "menu.h"

struct Candidate {
    std::string path;
    SDL_Texture* texture;
};

class QuizEngine {
public:
    QuizEngine(SDL_Renderer* renderer, TTF_Font* font);
    ~QuizEngine();

    bool loadCategory(const std::string& categoryName);
    void nextDuel();
    void selectWinner(int index); // 0 dla lewego, 1 dla prawego
    void render();
    void handleEvents(SDL_Event& event, GameState& currentState);

    

    bool isFinished() { return showFinalWinner; }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<Candidate> participants;   // Osoby czekające na swoją kolej w rundzie
    std::vector<Candidate> winnersCircle;  // Zwycięzcy aktualnej rundy
    Candidate currentLeft;
    Candidate currentRight;
    bool hasActiveDuel = false;
    SDL_Rect rectL = { 100, 200, 700, 600 };
    SDL_Rect rectR = { 1120, 200, 700, 600 };
    bool showFinalWinner = false;
    Candidate finalWinner;
    int round_number = 1;
    void reset();

    
};

#endif