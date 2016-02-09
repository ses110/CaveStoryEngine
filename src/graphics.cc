#include "graphics.h"

#include <SDL/SDL.h>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kBPP = 32;
}

Graphics::Graphics() {
    screen_ = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kBPP, SDL_FULLSCREEN);
}

Graphics::~Graphics() {
    SDL_FreeSurface(screen_);
}


void Graphics::blitSurface(SDL_Surface* source,
                     SDL_Rect* source_rectangle,
                     SDL_Rect* destination_rectangle) { 
    SDL_BlitSurface(source, source_rectangle, screen_, destination_rectangle);
}