#pragma once

#include "object.hpp"

namespace mal {
    class Brick: public Object {
        Brick(float x, float y, float width, float height, ObjectType type);
        virtual ~Brick() = default;

        char get_symbol() const override;
    };
}