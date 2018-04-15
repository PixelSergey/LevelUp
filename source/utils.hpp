#ifndef UTILS_HPP
#define UTILS_HPP

SDL_Surface* loadImage(const char path[]);
void draw(SDL_Surface* source, SDL_Surface* destination, int x, int y);

class Button{
private:
    SDL_Rect coords;
    SDL_Surface* image;
    SDL_Surface* screen;
    int x;
    int y;
public:
    Button(const char path[], SDL_Surface* screen, int x, int y);
    void draw();
    bool isClicked(int mouseX, int mouseY);
};

#endif
