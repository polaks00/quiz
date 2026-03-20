#include "quiz.h"
#include <iostream>

QuizEngine::QuizEngine(SDL_Renderer* r, TTF_Font* f) : renderer(r), font(f) {}
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

    if (participants.size() < 2) 
    {
        if (!participants.empty()) 
        {
            winnersCircle.push_back(participants.back());
            participants.pop_back();
        }
        if (winnersCircle.size() >= 2) 
        {
            participants = winnersCircle;
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(participants.begin(), participants.end(), g);
            winnersCircle.clear();
            round_number++;
        } 
        else 
        {
            return; 
        }
    }

    
    if (participants.size() >= 2) 
    {
        currentLeft = participants[participants.size() - 1];
        currentRight = participants[participants.size() - 2];
        hasActiveDuel = true;
    }
}

void QuizEngine::selectWinner(int index) {
    if (index == 0) winnersCircle.push_back(currentLeft);
    else winnersCircle.push_back(currentRight);

    participants.pop_back();
    participants.pop_back();
    
    if (participants.empty() && winnersCircle.size() == 1) 
    {
        finalWinner = winnersCircle[0];
        showFinalWinner = true;
        hasActiveDuel = false;
    } 
    else 
    {
        nextDuel();
    }
}

void QuizEngine::render() {
    std::string text_to_show="";
    if (showFinalWinner) {
        SDL_Rect centerRect = { 610, 240, 700, 600 }; 
        SDL_RenderCopy(renderer, finalWinner.texture, NULL, &centerRect);

        // Napis ZWYCIĘZCA
        text_to_show = "TOP1!";
        
    } 
    else if (hasActiveDuel) 
    {
        SDL_RenderCopy(renderer, currentLeft.texture, NULL, &rectL);
        SDL_RenderCopy(renderer, currentRight.texture, NULL, &rectR);
        text_to_show = "ROUND " + std::to_string(round_number);
    }
    SDL_Color gold = {255, 215, 0, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text_to_show.c_str(), gold);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    
    int tw, th;
    SDL_QueryTexture(tex, NULL, NULL, &tw, &th);
    SDL_Rect textPos = { 960 - tw/2, 100, tw, th };
    
    SDL_RenderCopy(renderer, tex, NULL, &textPos);
    
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex); 
}
void QuizEngine::handleEvents(SDL_Event& event, GameState& currentState) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
        if(showFinalWinner)
        {
            currentState = GameState::MAIN_MENU;
            reset();
        }
        else
        {
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
}

void QuizEngine::reset() {
    for(auto& p : participants) SDL_DestroyTexture(p.texture);
    for(auto& w : winnersCircle) SDL_DestroyTexture(w.texture);
    
    SDL_DestroyTexture(finalWinner.texture);

    round_number = 1;
    participants.clear();
    winnersCircle.clear();
    showFinalWinner = false;
    hasActiveDuel = false;
}