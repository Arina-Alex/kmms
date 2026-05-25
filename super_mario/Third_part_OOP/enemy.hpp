#pragma once

#include "moving.hpp"
#include "vector.hpp"

namespace mal {
    class Brick;
    
    class Enemy : public Moving {
        public:
            Enemy(): Moving(3, 2, TYPE_ENEMY, 0) {}
            Enemy(float x, float y);
            ~Enemy() = default;

            char get_symbol() const override;
            void update() override;

            bool has_ground_under(const Vector<Brick>& bricks) const;
    };
}

