#include "Enemy.h"
#include "Bounding_Box.h"

#include <bn_display.h>
#include <bn_math.h>
#include "bn_sprite_items_square.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;
static constexpr bn::size ENEMY_SIZE = {8, 8};

Enemy::Enemy(bn::fixed starting_x, bn::fixed starting_y, bn::size enemy_size) :
    sprite(bn::sprite_items::square.create_sprite(starting_x, starting_y)),
    speed(.8),
    size(enemy_size),
    bounding_box(create_bounding_box(sprite, size))
{}

void Enemy::update(Player& player) {
    if (sprite.x() > player.sprite.x()) {
        bn::fixed x_movement = bn::min(speed, sprite.x() - player.sprite.x());
        sprite.set_x(sprite.x() - x_movement);
    }
    if (sprite.x() < player.sprite.x()) {
        bn::fixed x_movement = bn::min(speed, player.sprite.x() - sprite.x());
        sprite.set_x(sprite.x() + x_movement);
    }

    if (sprite.y() > player.sprite.y()) {
        bn::fixed y_movement = bn::min(speed, sprite.y() - player.sprite.y());
        sprite.set_y(sprite.y() - y_movement);
    }
    if (sprite.y() < player.sprite.y()) {
        bn::fixed y_movement = bn::min(speed, player.sprite.y() - sprite.y());
        sprite.set_y(sprite.y() + y_movement);
    }

    bounding_box = create_bounding_box(sprite, size);
}

void Enemy::enemy_interact(Enemy& other_enemy) {
    if(sprite.x() > other_enemy.sprite.x()) {
        sprite.set_x(sprite.x() + (ENEMY_SIZE.width() / 2));
        other_enemy.sprite.set_x(other_enemy.sprite.x() - (ENEMY_SIZE.width() / 2));
    }
    
    if(sprite.x() < other_enemy.sprite.x()) {
        sprite.set_x(sprite.x() - (ENEMY_SIZE.width() / 2));
        other_enemy.sprite.set_x(other_enemy.sprite.x() + (ENEMY_SIZE.width() / 2));
    }
    
    if(sprite.y() > other_enemy.sprite.y()) {
        sprite.set_y(sprite.y() + (ENEMY_SIZE.height() / 2));
        other_enemy.sprite.set_y(other_enemy.sprite.y() - (ENEMY_SIZE.height() / 2));
    }
    
    if(sprite.y() < other_enemy.sprite.y()){
        sprite.set_y(sprite.y() - (ENEMY_SIZE.height() / 2));
        other_enemy.sprite.set_y(other_enemy.sprite.y() + (ENEMY_SIZE.height() / 2));
    }

    bounding_box = create_bounding_box(sprite, size);
    other_enemy.bounding_box = create_bounding_box(other_enemy.sprite, other_enemy.size);
}

void Enemy::respawn() {
    sprite.set_x(rand_spawn.get_int(MIN_X, MAX_X));
    sprite.set_y(rand_spawn.get_int(MIN_Y, MAX_Y));
    bounding_box = create_bounding_box(sprite, size);
}

