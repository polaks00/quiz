#include "menu.h"
#include "quiz.h"


Menu::Menu(SDL_Renderer* renderer_quiz, TTF_Font* font, TTF_Font* title_font) : renderer(renderer_quiz)  
{
    SDL_Color red = {231,76,60,255};  
    createButton(mainButtons,810,600,300,80,red,"ZAMKNIJ",font);
    createButton(mainButtons,810,500,300,80,red,"START",font);
    std::vector<std::string> folderNames = getCategoriesFromData();
    int startX = 400;
    int startY = 300;
    int spacingY = 100;
    for (size_t i = 0; i < folderNames.size(); ++i) 
    {
    int currentY = startY + (i * spacingY);
    createButton(categoryButtons, startX, currentY, 400, 80, red, folderNames[i], font);
    }
    createButton(categoryButtons, 810, 800, 300, 60, red, "ANULUJ", font);


    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* titleSurf = TTF_RenderText_Blended(title_font, "PORA NA QUIZ :)", white);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurf);
    int tw, th;
    SDL_QueryTexture(titleTexture, NULL, NULL, &tw, &th);
    // Skalujemy tytuł, żeby był np. 2x większy niż przyciski
    titleRect = { 960 - (tw * 2) / 2, 100, tw * 2, th * 2 };
    
    SDL_FreeSurface(titleSurf);  
}
void Menu::createButton(std::vector<UI_Button> &button_localization, int x, int y, int w, int h, SDL_Color color, std::string text, TTF_Font* font)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font,text.c_str(),{255,255,255,255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    button_localization.push_back({{x,y,w,h},color,text,texture});
}
Menu::~Menu() 
{
    for(const auto& btn : mainButtons)
    {
        SDL_DestroyTexture(btn.textTexture);
    }
    for(const auto& btn : categoryButtons)
    {
        SDL_DestroyTexture(btn.textTexture);
    }
}
void Menu::render(GameState currentState) 
{
    if(currentState == GameState::MAIN_MENU)
    {
        for(const auto& btn : mainButtons)
        {
            SDL_Rect shadow = {btn.rect.x + 4, btn.rect.y +4, btn.rect.w, btn.rect.h};
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &shadow);
            SDL_SetRenderDrawColor(renderer, btn.color.r, btn.color.g, btn.color.b,255);
            SDL_RenderFillRect(renderer, &btn.rect);
            int tw,th;
            SDL_QueryTexture(btn.textTexture,NULL,NULL, &tw,&th);
            SDL_Rect textPos = {btn.rect.x + (btn.rect.w - tw)/2, btn.rect.y + (btn.rect.h - th)/2, tw, th};
            SDL_RenderCopy(renderer, btn.textTexture,NULL,&textPos);
        }
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    }
    if(currentState == GameState::CATEGORY_SELECT)
    {
        for(const auto& btn : categoryButtons)
        {
            SDL_Rect shadow = {btn.rect.x + 4, btn.rect.y +4, btn.rect.w, btn.rect.h};
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &shadow);
            SDL_SetRenderDrawColor(renderer, btn.color.r, btn.color.g, btn.color.b,255);
            SDL_RenderFillRect(renderer, &btn.rect);
            int tw,th;
            SDL_QueryTexture(btn.textTexture,NULL,NULL, &tw,&th);
            SDL_Rect textPos = {btn.rect.x + (btn.rect.w - tw)/2, btn.rect.y + (btn.rect.h - th)/2, tw, th};
            SDL_RenderCopy(renderer, btn.textTexture,NULL,&textPos);
        }
    }
    
    
}
int Menu::handleEvents(SDL_Event& event, GameState& currentState, QuizEngine* quiz) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (currentState == GameState::MAIN_MENU)
            {
                for(const auto& btn : mainButtons)
                {
                    if (isMouseOverButton(x, y, btn.rect))
                    {
                        if(btn.text == "ZAMKNIJ")
                        {
                            return  1;
                        }
                        if (btn.text == "START") 
                        {
                            currentState = GameState::CATEGORY_SELECT;
                        }
                    }
                }
            }
            if (currentState == GameState::CATEGORY_SELECT)
            {
                for(const auto& btn : categoryButtons)
                {
                    if (isMouseOverButton(x, y, btn.rect))
                    {
                        if(btn.text == "ANULUJ")
                        {
                            currentState = GameState::MAIN_MENU;
                        }
                        else
                        {
                            currentState = GameState::QUIZ_ACTIVE;
                            quiz->loadCategory(btn.text);
                        }
                    }
                }
            }
            /*if (currentState == GameState::QUIZ_ACTIVE) 
            {
                if (event.type == SDL_KEYDOWN) 
                {
                    if (event.key.keysym.sym == SDLK_LEFT) quiz->selectWinner(0);
                    if (event.key.keysym.sym == SDLK_RIGHT) quiz->selectWinner(1);
                }
            }  */                       
        }
        return 0;
    }
bool Menu::isMouseOverButton(int mouseX, int mouseY, const SDL_Rect& buttonRect) {
    return mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
           mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h);
}

    


std::vector<std::string> Menu::getCategoriesFromData() 
{
    std::vector<std::string> categories;
    std::string path = "/home/polaks00/uwufufu/quiz/data"; 
    for (const auto& entry : fs::directory_iterator(path)) 
    {
        if (entry.is_directory()) 
        {
            categories.push_back(entry.path().filename().string());
        }
    }

    return categories;
}