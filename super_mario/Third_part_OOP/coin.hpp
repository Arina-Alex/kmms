#pragma once
#include "moving.hpp"

namespace mal {
    class Coin : public Moving {
        public:
            Coin(float x, float y);
            ~Coin() = default;
            
            char get_symbol() const override;
            void update() override;
    };
} 