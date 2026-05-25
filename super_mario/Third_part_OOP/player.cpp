#include "constants.hpp"
#include "player.hpp"

namespace mal {
    Player::Player(): Moving(3, 3, TYPE_PLAYER, 0), 
        score(0),
        is_left(false),
        is_right(false),
        is_jump(false) {
            setX(39);
            setY(10);
    }

    char Player::get_symbol() const {
        return '@';
    }

    void Player::update() {
        if (is_left) {
            horiz_speed = -1.0f; 
        } else if (is_right) {
            horiz_speed = 1.0f;   
        } else {
            horiz_speed = 0;      
        }
        
        if (is_jump && !is_fly) {
            jump();
        }
        
        apply_gravity();
        move();

        is_jump = false;
    }

    void Player::jump() {
        vert_speed = JUMP_POWER;
        is_fly = true;
    }

    void Player::add_score(int points) {
        score += points;
    }

    void Player::reset_for_new_level() {
        setX(39);
        setY(10);
        vert_speed = 0;
        horiz_speed = 0;
        score = 0;

        is_fly = false;
        is_left = false;
        is_right = false;
        is_jump = false;
    }

    void Player::set_left(bool hold) {
        is_left = hold;
    }
    void Player::set_right(bool hold) {
        is_right = hold;
    }
    void Player::set_jump(bool jump) {
        is_jump = jump;
    }

    int Player::get_score() const {
        return score;
    }

    bool Player::get_jump() const { 
        return is_jump;
    }

    bool Player::is_left_hold() const {
        return is_left;
    }

    bool Player::is_right_hold() const {
        return is_right;
    }
}