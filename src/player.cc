#include "player.h"

#include "game.h"
#include "sprite.h"
#include "animated_sprite.h"
#include "graphics.h"

Player::Player(int x, int y) : 
    x_(x), 
    y_(y) {
    sprite_.reset(new AnimatedSprite(
        "content/MyChar.bmp", 
        0,0, Game::kTileSize, Game::kTileSize,
        15, 3));
}

void Player::update(int elapsed_time_ms) {
    sprite_->update(elapsed_time_ms);
}

void Player::draw(Graphics& graphics) {
    sprite_->draw(graphics, x_, y_);
}
