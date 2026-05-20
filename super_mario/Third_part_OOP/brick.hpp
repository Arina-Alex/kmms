#pragma once

#include "object.hpp"

namespace mal {
    class Brick: public Object {
        Brick(float width, float height, ObjectType type);
        virtual ~Brick() = default;

        chat get_symbol() const override;
    };
}