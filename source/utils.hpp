#ifndef UTILS_HPP
#define UTILS_HPP

SDL_Surface* loadImage(const char path[]);
void draw(SDL_Surface* source, SDL_Surface* destination, int x, int y);

#endif