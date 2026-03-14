#include "quiz.h"
#include <iostream>

QuizEngine::QuizEngine(SDL_Renderer* r) : renderer(r) {}

bool QuizEngine::loadCategory(const std::string& categoryName) {
    std::string path = "/home/polaks00/uwufufu/quiz/data/" + categoryName;
    participants.clear();
    winnersCircle.clear();

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string ext = entry.path().extension().string();
        if (ext == ".jpg" || ext == ".png") {
            SDL_Surface* surf = IMG_Load(entry.path().string().c_str());
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            participants.push_back({entry.path().string(), tex});
        }
    }

    // Mieszamy zawodników na start
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(participants.begin(), participants.end(), g);

    nextDuel();
    return !participants.empty();
}

void QuizEngine::nextDuel() {
    if (participants.size() >= 2) {
        currentLeft = &participants[participants.size() - 1];
        currentRight = &participants[participants.size() - 2];
    } else if (participants.size() == 1) {
        // Jeśli został jeden, przechodzi automatycznie do wyższej rundy
        winnersCircle.push_back(participants.back());
        participants.pop_back();
        nextDuel(); // Rekurencja, aby sprawdzić czy nowa runda rusza
    } else if (!winnersCircle.empty()) {
        // Nowa runda!
        participants = winnersCircle;
        winnersCircle.clear();
        nextDuel();
    }
}

void QuizEngine::selectWinner(int index) {
    if (index == 0) winnersCircle.push_back(*currentLeft);
    else winnersCircle.push_back(*currentRight);

    // Usuwamy obu z obecnej kolejki (pobraliśmy ich z końca wektora)
    participants.pop_back();
    participants.pop_back();

    if (!isFinished()) nextDuel();
}

void QuizEngine::render() {
    if (!currentLeft || !currentRight) return;

    // Wyświetlanie obrazków obok siebie (uproszczone skalowanie)
    SDL_Rect rectL = { 100, 240, 800, 600 };
    SDL_Rect rectR = { 1020, 240, 800, 600 };

    SDL_RenderCopy(renderer, currentLeft->texture, NULL, &rectL);
    SDL_RenderCopy(renderer, currentRight->texture, NULL, &rectR);
}