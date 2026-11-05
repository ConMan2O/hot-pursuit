#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>

class Player {
    public:

        bn::sprite_ptr sprite;
        bn::fixed speed;
        bn::size size;
        bn::rect bounding_box;

        Player(bn::fixed x, bn::fixed y);  
        void update();                      
};

#endif