#pragma once

#include "object.hpp"

namespace mal {
    class moving : public object {
        protected:
            float vert_speed;
            float horiz_speed;  
            bool is_fly; 

        public:
            moving(float wigth, float height, ObjectType type, float h_speed);
            virtual ~moving() = default;

            virtual void update() override = 0;

            float get_vert_speed() const;
            float get_horiz_speed() const;
            bool is_fly() const;

            void set_vert_speed(float speed);
            void set_horiz_speed(float speed);
            void is_fly(bool fly);

            void add_vert_speed(float dspeed);
            void add_horiz_speed(float dspeed);

            void apply_gravity();
            void move();

    } 
}
