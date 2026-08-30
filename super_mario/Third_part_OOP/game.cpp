#include <iostream>
#include <windows.h>

#include "game.hpp"

namespace mal {

    Game::Game():
        current_level(1),
        max_level(3),
        is_running(true) {
            create_level(current_level);
        }

    void Game::put_object_on_map(const Object& obj) {
        int ix = static_cast<int>(obj.x());
        int iy = static_cast<int>(obj.y());
        int iw = static_cast<int>(obj.get_width());
        int ih = static_cast<int>(obj.get_height());
    
        for (int i = ix; i < ix + iw && i < MAP_WIDTH; ++i) {
            for (int j = iy; j < iy + ih && j < MAP_HEIGHT; ++j) {
                if (i >= 0 && j >= 0) {
                    map.set_cell(i, j, obj.get_symbol());
                }
            }
        }
    }
    void Game::horizon_move(float dx) {
        player.addX(-dx);
        
        for (int i = 0; i < bricks.get_size(); ++i) {
            if (player.collision_with(bricks[i])) {
                player.addX(dx);
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

    void Game::spawn_coin(const Brick& b) {
        Coin c(b.x() + b.get_width() / 2.0f, b.y() - 3);
        c.set_horiz_speed((rand() % 2) ? COIN_SPEED : -COIN_SPEED);
        coins.push_back(c);
    }

    void Game::check_brick_collision(Moving& obj, bool is_player) {
        for (int i = 0; i < bricks.get_size(); ++i) {
            Brick& b = bricks[i];
            if (!obj.collision_with(b)) continue;

            // перекрытие диапазонов ДО движения
            bool x_before = (obj.get_prev_x() + obj.get_width())  > b.x() &&
                            obj.get_prev_x() < (b.x() + b.get_width());
            bool y_before = (obj.get_prev_y() + obj.get_height()) > b.y() &&
                            obj.get_prev_y() < (b.y() + b.get_height());

            bool vertical = x_before && !y_before;
            bool horizontal = y_before && !x_before;

            // угол: решаем по вертикали, если по ней вообще было движение
            if (!vertical && !horizontal) {
                vertical = (obj.y() != obj.get_prev_y());
            }

            if (vertical) {
                if (obj.y() > obj.get_prev_y()) {          // падал -> встал сверху
                    obj.setY(b.y() - obj.get_height());
                    obj.set_vert_speed(0);
                    obj.is_flying(false);
                } else {                                   // летел вверх -> ударился головой
                    obj.setY(b.y() + b.get_height());
                    obj.set_vert_speed(0);

                    if (is_player && b.get_type() == TYPE_BONUS) {
                        b.set_type(TYPE_EMPTY_BONUS);
                        spawn_coin(b);
                    }
                }
            } else {                                       // упёрся в стену
                if (obj.x() > obj.get_prev_x())
                    obj.setX(b.x() - obj.get_width());
                else
                    obj.setX(b.x() + b.get_width());

                if (!is_player) obj.set_horiz_speed(-obj.get_horiz_speed());
            }

            if (is_player && b.get_type() == TYPE_GOAL) {
                next_level();
                return;                 // ОБЯЗАТЕЛЬНО: bricks уже пересоздан!
            }
        }
    }
    // void Game::check_brick_collision(Moving& obj, bool is_player) {
    //     for (int i = 0; i < bricks.get_size(); ++i) {
    //         if (obj.collision_with(bricks[i])) {
    //             float obj_bottom_before = obj.y() + obj.get_height() - obj.get_vert_speed();
                
    //             if (obj.get_vert_speed() > 0 && obj_bottom_before <= bricks[i].y() + 5) {
    //                 obj.setY(bricks[i].y() - obj.get_height());
    //                 obj.set_vert_speed(0);
    //                 obj.is_flying(false);
    //             }
    //             else if (obj.get_vert_speed() < 0 && is_player) {
    //                 obj.setY(bricks[i].y() + bricks[i].get_height());
    //                 obj.set_vert_speed(0);
                    
    //                 if (bricks[i].get_type() == TYPE_BONUS) {
    //                     bricks[i].set_type(TYPE_EMPTY_BONUS);
    //                     Coin newCoin(bricks[i].x(), bricks[i].y() - 3);
    //                     newCoin.set_vert_speed(-0.5f);
    //                     coins.push_back(newCoin);
    //                 }
    //             }
    //             else {
    //                 if (obj.x() < bricks[i].x()) {
    //                     obj.setX(bricks[i].x() - obj.get_width());
    //                 } else {
    //                     obj.setX(bricks[i].x() + bricks[i].get_width());
    //                 }
    //             }

    //             if (is_player && bricks[i].get_type() == TYPE_GOAL) {
    //                 next_level();
    //             }
    //             break;
    //         }
    //     }
    // }

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
        map.clear();

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
        map.put_score(player.get_score());
        map.set_cursor(0,0);
        map.draw();
    }



    void Game::update() {
        player.update();
        check_brick_collision(player, true);

        for (int i = 0; i < enemies.get_size(); ++i) {
            enemies[i].update();
            check_brick_collision(enemies[i], false);

            if (!enemies[i].is_flying() && 
                enemies[i].has_ground_under(bricks) && 
                !enemies[i].has_ground_ahead(bricks)) {
                enemies[i].set_horiz_speed(-enemies[i].get_horiz_speed());
            }

            if (enemies[i].y() > MAP_HEIGHT) {
                enemies.remove(i);
                i--;
            }
    
        }
        for (int i = 0; i < coins.get_size(); ++i) {
            coins[i].update();
            check_brick_collision(coins[i], false);

            if (!coins[i].is_flying() && !has_ground_under(coins[i])) {
                coins[i].set_horiz_speed(-coins[i].get_horiz_speed());
            }

            if (coins[i].y() > MAP_HEIGHT) { 
                coins.remove(i); --i; 
            }
        

            // if (coins[i].y() > MAP_HEIGHT || coins[i].y() + coins[i].get_height() < 0) {
            //     coins.remove(i);
            //     i--;
            // }
        }

        check_enemy_collision();
        check_coin_collision();
        // check_collision();
        if (player.y() + player.get_height() > MAP_HEIGHT) {
            player_dead();
            return;
        }
    }

    void Game::create_level(int level) {
        system("color 3D");
        
        bricks.clear();
        enemies.clear();
        coins.clear();
            
        player.reset_for_new_level();

            
        if (level == 1) {
            bricks.push_back(Brick(20, 20, 40, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(30, 10, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(50, 10, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(60, 15, 40, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(60, 5, 10, 3, TYPE_EMPTY_BONUS));
            bricks.push_back(Brick(70, 5, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(75, 5, 5, 3, TYPE_EMPTY_BONUS));
            bricks.push_back(Brick(80, 5, 5, 3, TYPE_BONUS));
            bricks.push_back(Brick(85, 5, 10, 3, TYPE_EMPTY_BONUS));
            bricks.push_back(Brick(100, 20, 20, 5, TYPE_PLATFORM));
            bricks.push_back(Brick(120, 15, 10, 10, TYPE_PLATFORM));
            bricks.push_back(Brick(150, 20, 40, 5, TYPE_PLATFORM));
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

    bool Game::has_ground_under(const Object& obj) const {
        float foot = obj.y() + obj.get_height() + 0.5f;
        for (int i = 0; i < bricks.get_size(); ++i) {
            const Brick& b = bricks[i];
            if (obj.x() + obj.get_width() > b.x() &&
                obj.x() < b.x() + b.get_width() &&
                foot >= b.y() && foot <= b.y() + b.get_height()) {
                return true;
            }
        }
        return false;
    }

    // bool Game::has_ground_at(float x, float y) const {
    //     for (int i = 0; i < bricks.get_size(); ++i) {
    //         const Brick& b = bricks[i];
    //         if (x >= b.x() && x < b.x() + b.get_width() &&
    //             y >= b.y() && y < b.y() + b.get_height())
    //             return true;
    //     }
    //     return false;
    // }

    void Game::run() {
        // const DWORD FRAME_MS = 33;
        while (is_running) {
            // DWORD frame_start = GetTickCount();
            input();
            
            if (player.is_left_hold()) {
                horizon_move(1.1f);
            }
            if (player.is_right_hold()) {
                horizon_move(-1.1f);
            }
            
            update();
            render();

            // DWORD elapsed = GetTickCount() - frame_start;
            // if (elapsed < FRAME_MS) Sleep(FRAME_MS - elapsed);
            
            Sleep(10);
        }
    }
}