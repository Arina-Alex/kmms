#pragma once

#include "object.hpp"

namespace mal {
    class Brick: public Object {
        public:
            Brick(): Object(0, 0, TYPE_AIR) {}
            Brick(float x, float y, float width, float height, ObjectType type);
            ~Brick() = default;
        private:
            char get_symbol() const override;
    };
}