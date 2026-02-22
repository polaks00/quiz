#include "menu.h"



    Menu::Menu(SDL_Renderer* renderer_quiz, TTF_Font* font) 
        : renderer(renderer_quiz)
    {
        SDL_Color red = {231,76,60,255};  

        createButton(810,500,300,80,red,"ZAMEK",font);
    }

    void Menu::createButton(int x, int y, int w, int h, SDL_Color color, std::string text, TTF_Font* font)
    {
        SDL_Surface* surface = TTF_RenderText_Blended(font,text.c_str(),{255,255,255,255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);

        buttons.push_back({{x,y,w,h},color,text,texture});
    }

    Menu::~Menu() 
    {
        for(const auto& btn : buttons)
        {
            SDL_DestroyTexture(btn.textTexture);
        }
    }

    void Menu::render() 
    {
        for(const auto& btn : buttons)
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

    int Menu::handleEvents(SDL_Event& event) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for(const auto& btn : buttons)
                {
                    if (isMouseOverButton(x, y, btn.rect))
                    {
                        std::cout << "Klikto przycisk " << std::endl; 
                        SDL_Event windowEvent;
                        
                        
                        printf("wyszedlem z petli \n");
                        return  1;
                    }
                }
            }
            return 0;
        }

    bool Menu::isMouseOverButton(int mouseX, int mouseY, const SDL_Rect& buttonRect) {
        return mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
               mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h);
    }

    
