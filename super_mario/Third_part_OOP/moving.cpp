#include "moving.hpp"

namespace mal{             
    Moving::Moving(float width, float height, ObjectType type, float h_speed) : 
      Object(width, height, type),
      vert_speed(0), 
      horiz_speed(h_speed),     
      is_fly(false),
      prev_x(0), prev_y(0)
    {}

    float Moving::get_vert_speed() const {
        return vert_speed;
    }
    float Moving::get_horiz_speed() const {
        return horiz_speed;
    }
    bool Moving::is_flying() const {
        return is_fly;
    }
    float Moving::get_prev_x() const { 
        return prev_x; 
    }
    float Moving::get_prev_y() const { 
        return prev_y; 
    }

    void Moving::set_vert_speed(float speed) {
        vert_speed = speed;
    }
    void Moving::set_horiz_speed(float speed) {
        horiz_speed = speed;
    }
    void Moving::is_flying(bool fly) {
        is_fly = fly;
    }

    void Moving::add_vert_speed(float dspeed) {
        vert_speed += dspeed;
    }
    void Moving::add_horiz_speed(float dspeed) {
        horiz_speed += dspeed;
    }

    void Moving::apply_gravity() {
        vert_speed += GRAVITY;
    }

    void Moving::move() {
        prev_x = _x;
        prev_y = _y;
        addX(horiz_speed);
        addY(vert_speed);
    }
}