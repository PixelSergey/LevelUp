#include <string.h>
#include <stdio.h>
#include <vector>

#include <3ds.h>
#include "SDL/SDL.h"

#include "main.hpp"
#include "utils.hpp"


SDL_Surface* screen = NULL;
SDL_Surface* hello = NULL;
SDL_Surface* hello2 = NULL;
SDL_Surface* ball = NULL;

std::vector<Button> buttons;

int x = 20;
int y = 20;
bool running = true;
bool test = false;
SDL_Event event;

bool init(){
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        return false;
    }
    
    // 480 = TOP_SCREEN HEIGHT + BOTTOM_SCREEN HEIGHT
    screen = SDL_SetVideoMode(400, 480, 16, SDL_DUALSCR);
    if(screen == NULL){
        return false;
    }
    SDL_ShowCursor(SDL_DISABLE);

    Result rc = romfsInit();
    if(rc){
        printf("romfsInit: %08lX\n", rc);
        SDL_Quit();
        return false;
    }
    
    hello = loadImage("romfs:/hello.png");
    hello2 = loadImage("romfs:/hello_bottom.png");
    ball = loadImage("romfs:/ball.png");
    buttons.push_back(Button("romfs:/button.png", screen, 50, 320));
    return true;
}

int main(int argc, char **argv){
    if(!init()) return 1;
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
                if(buttons[0].isClicked(x, y)){
                    test = true;
                }
            }
        }
        if(!running) break;
        
        SDL_GetMouseState(&x,&y);
        draw(hello, screen, 0, 0);
        draw(hello2, screen, 40, 240);
        if(!test) buttons[0].draw();
        draw(ball, screen, x, y);
        SDL_Flip(screen);
        
    }
    
    quit();
    return 0;
}

void quit(){
    SDL_FreeSurface(hello);
    SDL_FreeSurface(hello2);
    SDL_Quit();
}
