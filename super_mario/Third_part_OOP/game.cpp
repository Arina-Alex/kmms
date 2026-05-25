#include <windows.h>
#include <iostream>

#include "game.hpp"

namespace mal {

    void Game::clear_map() {
        for (int i = 0; i < MAP_WIDTH; ++i) {
            map[0][i] = ' ';
        }
        map[0][MAP_WIDTH] = '\0';
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            sprintf_s(map[j], MAP_WIDTH + 1, "%s", map[0]);
        }
    }

    void Game::draw_map() const {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            std::cout << map[j];
        }
    }

    void Game::horizon_move(float dx) {
        player.addX(dx);
        
        for (int i = 0; i < bricks.get_size(); ++i) {
            if (player.collision_with(bricks[i])) {
                player.addX(-dx);
                return;
            }
        }
        player.addX(dx);

        for (int i = 0; i < bricks.get_size(); ++i) {
            bricks[i].addX(dx);
        }
        for (int i = 0; i < enemies.get_size(); ++i) {
            enemies[i].addX(dx);
        }
        for (int i = 0; i < coins.get_size(); ++i) {
            coins[i].addX(dx);
        }
    }

    void Game::put_object_on_map(const Object& obj) {
        int ix = static_cast<int>(obj.x());
        int iy = static_cast<int>(obj.y());
        int iw = static_cast<int>(obj.get_width());
        int ih = static_cast<int>(obj.get_height());
    
        for (int i = ix; i < ix + iw && i < MAP_WIDTH; ++i) {
            for (int j = iy; j < iy + ih && j < MAP_HEIGHT; ++j) {
                if (i >= 0 && j >= 0) {
                    map[j][i] = obj.get_symbol();
                }
            }
        }
    }

    void Game::put_score_on_map() {
        char c[30];
        sprintf_s(c, "Score %d", player.get_score());
        int len = strlen(c);
        for (int i = 0; i < len; ++i) {
            map[1][i + 5] = c[i];
        }
    }

    void Game::check_coin_collision() {
        for (int i = 0; i < coins.get_size(); ++i) {
            if (player.collision_with(coins[i])) {
                player.add_score(100);
                coins.remove(i);
                i--;
            }
        }
    }

    void Game::check_collision() {
        check_brick_collision(player, true);
        check_enemy_collision();
        check_coin_collision();
        
        // // Для врагов (как в horizon_move_object для врагов)
        // for (int i = 0; i < enemies.get_size(); ++i) {
        //     for (int j = 0; j < bricks.get_size(); ++j) {
        //         if (enemies[i].collision_with(bricks[j])) {
        //             enemies[i].addX(-enemies[i].get_horiz_speed());
        //             enemies[i].get_horiz_speed(-enemies[i].get_horiz_speed());
        //             break;
        //         }
        //     }
        // }
    }

    void Game::check_enemy_collision() {
        for (int i = 0; i < enemies.get_size(); ++i) {
            if (player.collision_with(enemies[i])) {
                if (player.is_flying() && player.get_vert_speed() > 0 &&
                    player.y() + player.get_height() < enemies[i].y() + enemies[i].get_height() * 0.5f) {
                    player.add_score(50);
                    enemies.remove(i);
                    i--;
                    continue;
                } else {
                    player_dead();
                }
            }
        }
    }

    void Game::check_brick_collision(Moving& obj, bool is_player) {
        for (int i = 0; i < bricks.get_size(); ++i) {
            if (obj.collision_with(bricks[i])) {

                if (obj.get_vert_speed() > 0) {
                    obj.is_flying(false);
                }

                if (is_player && bricks[i].get_type() == TYPE_BONUS && obj.get_vert_speed() < 0) {
                    bricks[i].set_type(TYPE_EMPTY_BONUS);
                    Coin new_coin(bricks[i].x(), bricks[i].y() - 3);
                    new_coin.set_vert_speed(-0.5f);
                    coins.push_back(new_coin);
                }
                
                obj.addY(-obj.get_vert_speed());
                obj.set_vert_speed(0);
                
                if (is_player && bricks[i].get_type() == TYPE_GOAL) {
                    next_level();
                }
                break;
            }
        }
    }

    void Game::input() {
        player.set_left(GetKeyState('A') < 0);
        player.set_right(GetKeyState('D') < 0);

        if (GetKeyState(VK_SPACE) < 0 && !player.get_jump()) {
            player.set_jump(true);
        }
        
        if (GetKeyState(VK_ESCAPE) < 0) {
            is_running = false;
        }
    }

    void Game::render() {
        clear_map();

        for (int i = 0; i < bricks.get_size(); ++i) {
            put_object_on_map(bricks[i]);
        }
        
        for (int i = 0; i < enemies.get_size(); ++i) {
            put_object_on_map(enemies[i]);
        }

        for (int i = 0; i < coins.get_size(); ++i) {
            put_object_on_map(coins[i]);
        }
        
        put_object_on_map(player);
        set_cur(0, 0);
        draw_map();
    }

    void Game::set_cur(int x, int y) {
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    
    void Game::update() {
        player.update();
        for (int i = 0; i < enemies.get_size(); ++i) {
            enemies[i].update();
        }
        check_collision();
        for (int i = 0; i < coins.get_size(); ++i) {
            coins[i].update();
        }
    }

    void Game::create_level(int level) {
        system("color 3D");
    
        clear_map(); 
        
        bricks.clear();
        enemies.clear();
        coins.clear();
            
        player.reset_for_new_level();

            
        if (level == 1) {
            bricks.push_back(Brick(20, 20, 40, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(30, 10, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(50, 10, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(210, 15, 10, 10, TYPE_GOAL));
            
            enemies.push_back(Enemy(25, 10));
            enemies.push_back(Enemy(80, 10));
        }

        if (level == 2) {
            bricks.push_back(Brick(20, 20, 40, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(60, 15, 10, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(80, 20, 20, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(120, 15, 10, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(150, 20, 40, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(210, 15, 10, 10, TYPE_GOAL));
            
            enemies.push_back(Enemy(25, 10));
            enemies.push_back(Enemy(80, 10));
            enemies.push_back(Enemy(65, 10));
            enemies.push_back(Enemy(120, 10));
            enemies.push_back(Enemy(160, 10));
            enemies.push_back(Enemy(175, 10));
        }
        
        if (level == 3) {
            bricks.push_back(Brick(20, 20, 40, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(80, 20, 15, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(120, 15, 15, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(160, 10, 15, 15, TYPE_GOAL));
            
            enemies.push_back(Enemy(25, 10));
            enemies.push_back(Enemy(50, 10));
            enemies.push_back(Enemy(80, 10));
            enemies.push_back(Enemy(90, 10));
            enemies.push_back(Enemy(120, 10));
            enemies.push_back(Enemy(130, 10));
        }
    }

    void Game::next_level() {
        current_level++;
        if (current_level > max_level) {
            current_level = 1;
        }
        system("color 2F");
        Sleep(500);
        create_level(current_level);
    }

    void Game::player_dead() {
        system("color 4F");
        Sleep(500);
        create_level(current_level);
    }
    
    Game::Game(): current_level(1), max_level(3), is_running(true) {
        player.reset_for_new_level();
        create_level(current_level);
    }

    void Game::run() {
        while (is_running) {
            input();
            
            if (player.is_left_hold()) {
                horizon_move(2);
            }
            if (player.is_right_hold()) {
                horizon_move(-2);
            }
            
            update();
            render();
            
            Sleep(10);
        }
    }
}