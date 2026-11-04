#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_sprite_text_generator.h>

/**
 * Displays a score and high score.
 *
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
 */
class ScoreDisplay {
    public:
        // Number of characters required to show two of the longest number possible in an int (-2147483647)
        static constexpr int MAX_SCORE_CHARS = 22;

        ScoreDisplay();

        /**
         * Increases score by 1 and updates high score if needed. Displays score and high score.
         */
        void update();

        /**
         * Displays a number at the given position
         */
        void show_number(int x, int y, int number);

        /**
         * Sets score back to 0. Does NOT reset high score.
         */
        void resetScore();

        int score; // current score
        int high_score; // best score
        bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
        bn::sprite_text_generator text_generator; // Text generator for scores
};

#endif