#pragma once

#include "moving.hpp"

namespace mal {
    class Player : public Moving {

        private:
            int score;
            bool is_left;
            bool is_right;
            bool is_jump;

        public:
            Player();
            ~Player() = default;

            char get_symbol() const override;
            void update() override;

            void set_left(bool hold);
            void set_right(bool hold);
            void set_jump(bool jump);

            void jump();             
            void add_score(int points);      
            void reset_for_new_level();            
            
            int get_score() const;
            bool is_left_hold() const;
            bool is_right_hold() const;
    };
}