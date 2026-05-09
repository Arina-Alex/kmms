#include "func.hpp"

int main() {
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    Object mario;
    Object* brick = nullptr;
    int brick_length = 0;
    Object* moving = nullptr; 
    int moving_length = 0;
    int level = 1;
    int max_lvl = 3;
    int score = 0;

    create_level(mario, max_lvl, level, score, brick, brick_length, moving, moving_length);

    do {
        clear_map(map);

        if (!mario.is_fly && (GetKeyState(VK_SPACE) < 0)) {
            mario.vert_speed = -2;
        }
        if (GetKeyState('A') < 0) {
            horizon_move_map(2, mario, brick, brick_length, 
                                moving, moving_length);
        }
        if (GetKeyState('D') < 0) {
            horizon_move_map(-2, mario, brick, brick_length, 
                                moving, moving_length);
        }
        if (mario.y > MAP_HEIGHT) {
            player_dead(mario, max_lvl, level, score, 
                        brick, brick_length, moving, moving_length);
        }
        vert_move_object(&mario, mario, level, max_lvl, score, 
                        brick, brick_length, moving, moving_length);

        mario_collision(mario, max_lvl, level, score, 
                        brick, brick_length, moving, moving_length);

        for (int i = 0; i < brick_length; i++) {
            put_object_on_map(brick[i], map);
        }

        for (int i = 0; i < moving_length; i++) {
            vert_move_object(moving + i, mario, level, max_lvl, score, 
                            brick, brick_length, moving, moving_length);
            horizon_move_object(moving + i, mario, level, max_lvl, score, 
                                brick, brick_length, moving, moving_length);
            if (moving[i].y > MAP_HEIGHT) {
                delete_moving(i, moving, moving_length);
                i--;
                continue;
            }
            put_object_on_map(moving[i], map);
        }
        
        put_object_on_map(mario, map);
        put_score_on_map(map, score);

        set_cur(0, 0);
        show_map(map);

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);

    delete[] brick;
    delete[] moving;
    
    return 0;
}