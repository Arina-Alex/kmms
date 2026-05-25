#pragma once

#include <windows.h>

#include "brick.hpp"
#include "coin.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "vector.hpp"


namespace mal {
    class Game {
        private:
            char map [MAP_HEIGHT][MAP_WIDTH+1];

            Player player;
            Vector<Brick> bricks;
            Vector<Enemy> enemies;
            Vector<Coin> coins;

            int current_level;
            int max_level;
            bool is_running;

            void clear_map();
            void draw_map() const;
            void horizon_move(float dx);
            void put_object_on_map(const Object& obj);
            void put_score_on_map();

            void input();
            void render();
            void set_cur(int x, int y);
            void update();

            void check_coin_collision();
            void check_collision();
            void check_enemy_collision();
            void check_brick_collision(Moving& obj, bool is_player);
            
            void create_level(int level);
            void next_level();
            void player_dead();
            
        public:
            Game();
            ~Game() = default;

            void run();
    };
}
