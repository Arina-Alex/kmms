#pragma once

#include <windows.h>

#include "brick.hpp"
#include "coin.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "player.hpp"
#include "vector.hpp"


namespace mal {
    class Game {
        private:
            Map map;

            Player player;
            Vector<Brick> bricks;
            Vector<Enemy> enemies;
            Vector<Coin> coins;

            int current_level;
            int max_level;
            bool is_running;

            void put_object_on_map(const Object& obj);

            void input();
            void render();
            void update();

            void check_coin_collision();
            void check_collision();
            void check_enemy_collision();
            void check_brick_collision(Moving& obj, bool is_player);
            
            void create_level(int level);
            void next_level();
            void player_dead();

            void horizon_move(float dx);

            void spawn_coin(const Brick& b);
            bool has_ground_under(const Object& obj) const;
            
        public:
            Game();
            ~Game() = default;

            void run();
    };
}
