#include "game.h"

#include <SDL/SDL.h>

#include "graphics.h"
#include "animated_sprite.h"

namespace {
    const int kFPS = 60;
}

int Game::kTileSize = 32;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
    eventLoop();
}
Game::~Game() {
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    SDL_Event event;

    sprite_.reset(new AnimatedSprite("content/MyChar.bmp", 0,0, kTileSize, kTileSize, 15, 3));

    bool running = true;
    int last_update_time = SDL_GetTicks();
    while (running) {
        const int start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }
        const int current_time_ms = SDL_GetTicks();
        update(current_time_ms - last_update_time);
        last_update_time = current_time_ms;

        draw(graphics);
        const int elapsed_time = SDL_GetTicks() - start_time;
        // SDL_Delay takes a Uint32. If elapsed_time longer than 1000/60 ms then you pass an underflowing number and app will hang
        if(elapsed_time < 1000/kFPS) {
            SDL_Delay(1000/kFPS - elapsed_time);
        }
    }
}

void Game::update(int elapsed_time_ms) {
    sprite_->update(elapsed_time_ms);
}
void Game::draw(Graphics& graphics) {
    sprite_->draw(graphics, 320, 240);
    graphics.flip();
}
