#include "game.h"

#include <SDL/SDL.h>

#include "graphics.h"
#include "player.h"
#include "input.h"

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
    Input input;
    SDL_Event event;

    player_.reset(new Player(320, 240));

    bool running = true;
    int last_update_time = SDL_GetTicks();
    while (running) {
        const int start_time = SDL_GetTicks();
        input.beginNewFrame();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    input.keyDownEvent(event);
                    break;
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                default:
                    break;
            }
        }
        if (input.wasKeyPressed(SDLK_ESCAPE)) {
            running = false;
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
    player_->update(elapsed_time_ms);
}
void Game::draw(Graphics& graphics) {
    player_->draw(graphics);
    graphics.flip();
}
