#pragma once

#include "object.hpp"

namespace mal {
    class Moving : public Object {
        protected:
            float vert_speed;
            float horiz_speed;  
            bool is_fly; 

        public:
            Moving(float width, float height, ObjectType type, float h_speed);
            virtual ~Moving() = default;

            virtual void update() = 0;

            float get_vert_speed() const;
            float get_horiz_speed() const;
            bool is_flying() const;

            void set_vert_speed(float speed);
            void set_horiz_speed(float speed);
            void is_flying(bool fly);

            void add_vert_speed(float dspeed);
            void add_horiz_speed(float dspeed);

            void apply_gravity();
            void move();
    };
}
