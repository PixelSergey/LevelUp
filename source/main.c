#include <string.h>
#include <stdio.h>

#include <3ds.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "main.h"

SDL_Surface* hello = NULL;
SDL_Surface* hello2 = NULL;
SDL_Surface* screen = NULL;
SDL_Event event;

bool init(){
	
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
	        return false;
	}
	
	// 480 = TOP_SCREEN HEIGHT + BOTTOM_SCREEN HEIGHT
	screen = SDL_SetVideoMode(400, 480, 32, SDL_DUALSCR);
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
	
	return true;
}

int main(int argc, char **argv){
	
	if(!init()) return 1;
	bool running = true;
	
	hello = loadImage("romfs:/hello.png");
	hello2 = loadImage("romfs:/hello_bottom.png");
	
	while(running){
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				SDLKey key = event.key.keysym.sym;
				if(key == SDLK_RETURN){
					running = false;
					break;
				}
			}
		}
		if(!running) break;
		
		draw(hello, screen, 0, 0);
		draw(hello2, screen, 40, 240);
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

SDL_Surface* loadImage(char path[]){
	
	SDL_Surface* rawImage = NULL;
	SDL_Surface* returnImage = NULL;
	
	rawImage = IMG_Load(path);
	if(rawImage != NULL){
		returnImage = SDL_DisplayFormatAlpha(rawImage);
		SDL_FreeSurface(rawImage);
	}
	
	return returnImage;
}

void draw(SDL_Surface* source, SDL_Surface* target, int x, int y){
	
	SDL_Rect coords;
	coords.x = x;
	coords.y = y;
	
	SDL_BlitSurface(source, NULL, target, &coords);
}
