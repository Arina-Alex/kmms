#include "object.hpp"

namespace mal{
    object::object(float wigth, float height, ObjectType type):
        width(_width), height(_height), type(_type) 
    {}

    float object::x() const {
        return _x;
    }
    float object::y() const {
        return _y;
    }
    float object::get_width() const {
        return _width;
    }
    float object::get_height() const {
        return _height;
    }
    ObjectType get_type() const {
        return _type;
    }
    void object::setX(float x) {
        _x = x;
    }
    void object::setY(float y) {
        _y = y;
    }
    void object::addX(float dx) {
        _x += dx;
    }
    void object::addY(float dy) {
        _y += dy;
    }
    void object::setPos(float x, float y) {
        _x = x;
        _y = y;
    }
    void object::setType(ObjectType type) {
        _type = type;
    }

    bool object::collision_with(const GameObject& other) const {
        bool x_over = (_x + _width) > other._x &&
            _x < (other._x + other._width);

        bool y_over = (_y + _width) > other._y &&
            _y < (other._y + other._width);
        
        return x_over && y_over;
    }
}
