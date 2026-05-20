#include "brick.hpp"

namespace mal {
    Brick::Brick(float x, float y, float width, float height, ObjectType type) :
        Object (width, height, type) {
            setX(x);
            setY(y);
    }
    char Brick::get_symbol() const {
        return _type;
    }
}