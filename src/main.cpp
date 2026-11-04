#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_random.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"
#include "Player.h"
#include "Bounding_Box.h"
#include "ScoreDisplay.h"
#include "Enemy.h"


static constexpr bn::size ENEMY_SIZE = {8, 8};
static constexpr int MAX_ENEMIES = 20;

int main() {
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    Player player = Player(44, 22);

    bn::vector<Enemy, MAX_ENEMIES> enemies = {};

    bool isCaught = false; // flag for if the player has been caught

    Enemy e1 = Enemy(-30, 10, ENEMY_SIZE);
    // Enemy e2 = Enemy(-20, 10, ENEMY_SIZE);
    // Enemy e3 = Enemy(-10, 10, ENEMY_SIZE);
    // Enemy e4 = Enemy(0, 10, ENEMY_SIZE);

    enemies.push_back(e1);
    // enemies.push_back(e2);
    // enemies.push_back(e3);
    // enemies.push_back(e4);

    while(true) {
        player.update();

        for(Enemy enemy : enemies) {
            enemy.update(player);
            if (enemy.bounding_box.intersects(player.bounding_box)) {
                isCaught = true; // set flag
            }
        }

        // Reset the current score and player position if the player collides with enemy
        if (isCaught) {
            scoreDisplay.resetScore();
            player.sprite.set_x(44);
            player.sprite.set_y(22);
            while (enemies.size() > 1) { // remove all but 1 enemy
                enemies.pop_back();
            }
            enemies.at(0).respawn();
            isCaught = false; // reset flag
        }

        // Update the scores and display them
        scoreDisplay.update();

        // Spawn an additional enemy every ~15 seconds
        if (enemies.size() < enemies.max_size() && scoreDisplay.score % 900 == 0) {
            enemies.push_back(Enemy(0, 0, ENEMY_SIZE));
            enemies.end()->respawn();
        }

        bn::core::update();
    }
}