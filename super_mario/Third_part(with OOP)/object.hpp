#pragma once

#include "constants.hpp"

namespace mal{
    class object{

        protected:

            float _x;
            float _y;
            float _width;
            float _height;
            ObjectType _type;

        public:
            object(float width, float height, ObjectType type);
            virtual ~object() = default;

            virtual char get_symbol() const = 0;

            float x() const;
            float y() const;
            float get_width() const;
            float get_height() const;
            ObjectType get_type() const;

            void setX(float x);
            void setY(float y);
            void addX(float dx);
            void addY(float dy);
            void setPos(float x, float y);
            void setType(ObjectType type);

            bool collision_with(const GameObject& other) const;
    }
}