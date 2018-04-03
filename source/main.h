#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED

bool init();
int main(int argc, char **argv);
void quit();
SDL_Surface *loadImage(char path[]);
void draw(SDL_Surface* source, SDL_Surface* destination, int x, int y);

#endif
