#include "map.hpp"
#include <iostream>
#include <windows.h>

namespace mal {

    Map::Map() {
        clear();
    }

    void Map::clear() {
        for (int i = 0; i < MAP_WIDTH; ++i) {
            map[0][i] = ' ';
        }
        map[0][MAP_WIDTH] = '\0';
        
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            sprintf_s(map[j], MAP_WIDTH + 1, "%s", map[0]);
        }
    }

    void Map::set_cell(int x, int y, char symbol) {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            map[y][x] = symbol;
        }
    }

    char Map::get_cell(int x, int y) const {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            return map[y][x];
        }
        return ' ';
    }

    void Map::draw() const {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            std::cout << map[j];
        }
    }

    void Map::set_cursor(int x, int y) const {
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void Map::put_score(int score) {
        char c[30];
        sprintf_s(c, "Score %d", score);
        int len = static_cast<int>(strlen(c));
        for (int i = 0; i < len && i + 5 < MAP_WIDTH; ++i) {
            map[1][i + 5] = c[i];
        }
    }

} 