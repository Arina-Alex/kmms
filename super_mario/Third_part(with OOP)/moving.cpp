#include "moving.hpp"

namespace mal{             
    moving::moving(float wigth, float height, ObjectType type, float h_speed) 
    : object(width, height, type)
    , vert_speed(0)  
    , horiz_speed(h_speed)     
    , is_fly(false)
    {}

    float moving::get_vert_speed() const {
        return vert_speed;
    }
    float moving::get_horiz_speed() const {
        return horiz_speed;
    }
    bool moving::is_fly() const {
        return is_fly;
    }

    void moving::set_vert_speed(float speed) {
        vert_speed = speed;
    }
    void moving::set_horiz_speed(float speed) {
        horiz_speed = speed;
    }
    void moving::is_fly(bool fly) {
        is_fly = fly;
    }

    void moving::add_vert_speed(float dspeed) {
        vert_speed += dspeed;
    }
    void moving::add_horiz_speed(float dspeed) {
        horiz_speed += dspeed;
    }

    void moving::apply_gravity() {
        if (!is_fly) {
            is_fly = true;
        }
        vert_speed += GRAVITY;
    }

    void moving::move() {
        addX(horiz_speed);
        addY(vert_speed);
    }
}