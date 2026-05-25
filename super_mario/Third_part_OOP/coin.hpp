#pragma once
#include "moving.hpp"

namespace mal {
    class Coin : public Moving {
        public:
            Coin(): Moving(3, 2, TYPE_MONEY, 0) {}
            Coin(float x, float y);
            ~Coin() = default;
            
            char get_symbol() const override;
            void update() override;
    };
} 