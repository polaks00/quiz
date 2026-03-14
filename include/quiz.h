#ifndef QUIZ_H
#define QUIZ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <filesystem>

struct Candidate {
    std::string path;
    SDL_Texture* texture;
};

class QuizEngine {
public:
    QuizEngine(SDL_Renderer* renderer);
    ~QuizEngine();

    bool loadCategory(const std::string& categoryName);
    void nextDuel();
    void selectWinner(int index); // 0 dla lewego, 1 dla prawego
    void render();

    bool isFinished() { return participants.size() < 2 && winnersCircle.empty(); }

private:
    SDL_Renderer* renderer;
    std::vector<Candidate> participants;   // Osoby czekające na swoją kolej w rundzie
    std::vector<Candidate> winnersCircle;  // Zwycięzcy aktualnej rundy
    Candidate* currentLeft = nullptr;
    Candidate* currentRight = nullptr;

    void clearTextures(std::vector<Candidate>& list);
};

#endif