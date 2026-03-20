#include "quiz.h"
#include <iostream>

QuizEngine::QuizEngine(SDL_Renderer* r) : renderer(r) {}
QuizEngine::~QuizEngine() {}

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
    hasActiveDuel = false;

    if (participants.size() < 2) {
        if (!participants.empty()) 
        {
            winnersCircle.push_back(participants.back());
            participants.pop_back();
        }
        if (winnersCircle.size() >= 2) 
        {
            participants = winnersCircle;
            winnersCircle.clear();
        } 
        else 
        {
            return; 
        }
    }

    
    if (participants.size() >= 2) {
        currentLeft = participants[participants.size() - 1];
        currentRight = participants[participants.size() - 2];
        printf("taki rozmiar part %d\n", participants.size());
        hasActiveDuel = true;
    }
}

void QuizEngine::selectWinner(int index) {
    if (index == 0) winnersCircle.push_back(currentLeft);
    else winnersCircle.push_back(currentRight);

    participants.pop_back();
    participants.pop_back();

    if (!isFinished()) nextDuel();
}

void QuizEngine::render() {
    if (!hasActiveDuel) return;

    if (currentLeft.texture && currentRight.texture) {
        

        SDL_RenderCopy(renderer, currentLeft.texture, NULL, &rectL);
        SDL_RenderCopy(renderer, currentRight.texture, NULL, &rectR);
    } else {
        std::cerr << "Błąd: Próba narysowania pustej tekstury!" << std::endl;
    }
}

void QuizEngine::handleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= rectL.x && mouseX <= (rectL.x + rectL.w) &&
            mouseY >= rectL.y && mouseY <= (rectL.y + rectL.h)) {
            selectWinner(0); // 0 = Lewy
        } 
        else if (mouseX >= rectR.x && mouseX <= (rectR.x + rectR.w) &&
                 mouseY >= rectR.y && mouseY <= (rectR.y + rectR.h)) {
            selectWinner(1); // 1 = Prawy
        }
    }
}