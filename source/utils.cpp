#include <string.h>
#include <stdio.h>

#include <3ds.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "utils.hpp"


SDL_Surface* loadImage(const char path[]){
	
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
