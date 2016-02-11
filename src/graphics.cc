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


Graphics::SurfaceID Graphics::loadImage(const std::string& file_path) {
    // If we have not loaded in the spritesheet
    if (sprite_sheets_.count(file_path) == 0) {
        //Load spritesheet
        sprite_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());
    }
    return sprite_sheets_[file_path];
}

void Graphics::blitSurface(SurfaceID source,
                     SDL_Rect* source_rectangle,
                     SDL_Rect* destination_rectangle) { 
    SDL_BlitSurface(source, source_rectangle, screen_, destination_rectangle);
}

void Graphics::clear() {
    SDL_FillRect(screen_, NULL, 0);
}

void Graphics::flip() {
    SDL_Flip(screen_);
}

