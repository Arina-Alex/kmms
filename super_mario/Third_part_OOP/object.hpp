#pragma once

#include "constants.hpp"

namespace mal{
    class Object{

        protected:

            float _x;
            float _y;
            float _width;
            float _height;
            ObjectType _type;

        public:
            Object(float width, float height, ObjectType type);
            virtual ~Object() = default;

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

            bool collision_with(const Object& other) const;
    };
}