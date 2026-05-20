#include "coin.hpp"
#include "constants.hpp"

namespace mal {

    Coin::Coin(float x, float y): Moving(3, 2, TYPE_MONEY, 0) {
        setX(x);
        setY(y);
        vert_speed = -0.5f;  
        is_fly = true;  
    }

    char Coin::get_symbol() const {
        return '$'; 
    }

    void Coin::update() {
        apply_gravity();
        move();
    }
}