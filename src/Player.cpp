#include "Player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_dot.h"
#include <bn_display.h>
#include "Bounding_Box.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;
static constexpr bn::size PLAYER_SIZE = {8, 8};

Player::Player(bn::fixed x, bn::fixed y) :
    sprite(bn::sprite_items::dot.create_sprite(x, y)),
    speed(1.5),
    size(PLAYER_SIZE),
    bounding_box(create_bounding_box(sprite, size)) 
{}

void Player::update() {
    if(bn::keypad::right_held()) {
                sprite.set_x(sprite.x() + speed);
            }
            if(bn::keypad::left_held()) {
                sprite.set_x(sprite.x() - speed);
            }
            if(bn::keypad::up_held()) {
                sprite.set_y(sprite.y() - speed);
            }
            if(bn::keypad::down_held()) {
                sprite.set_y(sprite.y() + speed);
            }
            
            bounding_box = create_bounding_box(sprite, size);

            // Adding border to game
            if (sprite.y() < MIN_Y)
            {
                sprite.set_y(MIN_Y);
            }
            if (sprite.y() > MAX_Y)
            {
                sprite.set_y(MAX_Y);
            }
            if (sprite.x() < MIN_X)
            {
                sprite.set_x(MIN_X);
            }
            if (sprite.x() > MAX_X )
            {
                sprite.set_x(MAX_X);
            }
};
