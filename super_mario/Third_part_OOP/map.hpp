#pragma once
#include "constants.hpp"

namespace mal {

class Map {
    private:
        char map[MAP_HEIGHT][MAP_WIDTH + 1];
        
    public:
        Map();

        void clear();
        void draw() const;
        char get_cell(int x, int y) const;
        void put_score(int score);
        void set_cell(int x, int y, char symbol);
        void set_cursor(int x, int y) const;
    };

} 