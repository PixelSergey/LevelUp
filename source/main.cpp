#include <string.h>
#include <stdio.h>
#include <map>

#include <3ds.h>
#include "SDL/SDL.h"

#include "main.hpp"
#include "utils.hpp"


SDL_Surface* screen = NULL;
std::map<std::string, SDL_Surface*> images;
std::map<std::string, Button> buttons;

bool init(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        return false;
    }
    
    // 480 = TOP_SCREEN HEIGHT + BOTTOM_SCREEN HEIGHT
    screen = SDL_SetVideoMode(400, 480, 16, SDL_DUALSCR);
    if(screen == NULL){
        SDL_Quit();
        return false;
    }
    SDL_ShowCursor(SDL_DISABLE);
    
    if(romfsInit()){
        SDL_Quit();
        return false;
    }
    
    images.emplace("hello", loadImage("romfs:/hello.png"));
    images.emplace("hello2", loadImage("romfs:/hello_bottom.png"));
    images.emplace("ball", loadImage("romfs:/ball.png"));
    
    buttons.emplace("btn", Button("romfs:/button.png", screen, 50, 320));
    return true;
}

int main(int argc, char **argv){
    if(!init()){SDL_Quit(); return 1;}
    
    int x = 20;
    int y = 20;
    bool running = true;
    bool test = false;
    SDL_Event event;
    while(running){
        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                SDLKey key = event.key.keysym.sym;
                if(key == SDLK_RETURN){
                    running = false;
                    break;
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                x = event.button.x;
                y = event.button.y;
                if(buttons.at("btn").isClicked(x, y)){
                    test = true;
                }
            }
        }
        if(!running) break;
        
        SDL_GetMouseState(&x,&y);
        draw(images.at("hello"), screen, 0, 0);
        draw(images.at("hello2"), screen, 40, 240);
        if(!test) buttons.at("btn").draw();
        draw(images.at("ball"), screen, x, y);
        
        SDL_Flip(screen);
        
    }
    
    quit();
    return 0;
}

void quit(){
    for(auto const& pair : images){
        SDL_FreeSurface(pair.second);
    }
    for(auto const& pair : buttons){
        pair.second.unload();
    }
    SDL_Quit();
}
