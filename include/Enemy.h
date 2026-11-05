#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_random.h>

#include "Player.h"

class Enemy {
    public:
        bn::sprite_ptr sprite;
        bn::fixed speed;
        bn::size size;
        bn::rect bounding_box;
        bn::random rand_spawn;

        Enemy(bn::fixed starting_x, bn::fixed starting_y, bn::size enemy_size);

        void update(Player& player);

        void enemy_interact(Enemy& other_enemy);

        void respawn();
};

#endif