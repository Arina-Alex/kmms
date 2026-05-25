#include "object.hpp"

namespace mal {
    Object::Object(float width, float height, ObjectType type):
        _width(width), _height(height), _type(type) 
    {}

    float Object::x() const {
        return _x;
    }
    float Object::y() const {
        return _y;
    }
    float Object::get_width() const {
        return _width;
    }
    float Object::get_height() const {
        return _height;
    }
    ObjectType Object::get_type() const{
        return _type;
    }
    void Object::setX(float x) {
        _x = x;
    }
    void Object::setY(float y) {
        _y = y;
    }
    void Object::addX(float dx) {
        _x += dx;
    }
    void Object::addY(float dy) {
        _y += dy;
    }
    void Object::set_pos(float x, float y) {
        _x = x;
        _y = y;
    }
    void Object::set_type(ObjectType type) {
        _type = type;
    }

    bool Object::collision_with(const Object& other) const {
        bool x_over = (_x + _width) > other._x &&
            _x < (other._x + other._width);

        bool y_over = (_y + _width) > other._y &&
            _y < (other._y + other._width);
        
        return x_over && y_over;
    }
}
