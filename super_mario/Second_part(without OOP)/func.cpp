#include "func.hpp"

void clear_map (char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        map[0][i] = ' ';
    }
    map[0][MAP_WIDTH] = '\0';
    for (int j = 0; j < MAP_HEIGHT; j++) {
        sprintf_s (map[j], MAP_WIDTH+1, "%s", map[0]);
    }
}

void create_level(Object& mario, int& max_lvl, int& level, int& score, 
    Object*& brick, int& brick_length, Object*& moving, int& moving_length) {
    system("color 3D");

    delete[] brick;
    brick = nullptr;
    brick_length = 0;

    delete[] moving;
    moving = nullptr;    
    moving_length = 0;

    init_object(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (level == 1) {
        init_object(get_new_brick(brick, brick_length), 20, 20, 40, 5, '#');
            init_object(get_new_brick(brick, brick_length), 30, 10, 5, 3, '?');
            init_object(get_new_brick(brick, brick_length), 50, 10, 5, 3, '?');
        init_object(get_new_brick(brick, brick_length), 60, 15, 40, 10, '#');
            init_object(get_new_brick(brick, brick_length), 60, 5, 10, 3, '-');
            init_object(get_new_brick(brick, brick_length), 70, 5, 5, 3, '?');
            init_object(get_new_brick(brick, brick_length), 75, 5, 5, 3, '-');
            init_object(get_new_brick(brick, brick_length), 80, 5, 5, 3, '?');
            init_object(get_new_brick(brick, brick_length), 85, 5, 10, 3, '-');
        init_object(get_new_brick(brick, brick_length), 100, 20, 20, 5, '#');
        init_object(get_new_brick(brick, brick_length), 120, 15, 10, 10, '#');
        init_object(get_new_brick(brick, brick_length), 150, 20, 40, 5, '#');
        init_object(get_new_brick(brick, brick_length), 210, 15, 10, 10, '+');
    
        init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
    }

    if (level == 2) {
        init_object(get_new_brick(brick, brick_length), 20, 20, 40, 5, '#');
        init_object(get_new_brick(brick, brick_length), 60, 15, 10, 10, '#');
        init_object(get_new_brick(brick, brick_length), 80, 20, 20, 5, '#');
        init_object(get_new_brick(brick, brick_length), 120, 15, 10, 10, '#');
        init_object(get_new_brick(brick, brick_length), 150, 20, 40, 5, '#');
        init_object(get_new_brick(brick, brick_length), 210, 15, 10, 10, '+');

        init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 65, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 175, 10, 3, 2, 'o');
    }

    if (level == 3) {
        init_object(get_new_brick(brick, brick_length), 20, 20, 40, 5, '#');
        init_object(get_new_brick(brick, brick_length), 80, 20, 15, 10, '#');
        init_object(get_new_brick(brick, brick_length), 120, 15, 15, 10, '#');
        init_object(get_new_brick(brick, brick_length), 160, 10, 15, 15, '+');

        init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 50, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 90, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(moving, moving_length), 130, 10, 3, 2, 'o');    
    }
    max_lvl = 3;
    
}

void delete_moving(int i, Object*& moving, int& moving_length) {
    moving_length--;
    moving[i] = moving[moving_length];

    Object* new_moving = new Object[moving_length];
    for (int j = 0; j < moving_length; j++) {
        new_moving[j] = moving[j];
    }
    delete[] moving; 
    moving = new_moving;
}

Object* get_new_brick(Object*& brick, int& brick_length) {
    Object* new_brick = new Object[brick_length + 1];
    for (int i = 0; i < brick_length; i++) {
        new_brick[i] = brick[i];
    }
    delete[] brick;
    brick = new_brick;
    brick_length++;
    return &brick[brick_length - 1];
}

Object* get_new_moving(Object*& moving, int& moving_length) {
    Object* new_moving = new Object[moving_length + 1];
    for (int i = 0; i < moving_length; i++) {
        new_moving[i] = moving[i];
    }
    delete[] moving;
    moving = new_moving;
    moving_length++;
    return &moving[moving_length - 1];
}

void horizon_move_map(float dx, Object& mario, Object*& brick, int& brick_length, 
                    Object*& moving, int& moving_length) {
    mario.x -= dx;
    for (int i = 0; i < brick_length; i++) {
        if (is_collision (mario, brick[i])) {
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;

    for (int i = 0; i < brick_length; i++) {
        brick[i].x += dx;
    }

    for (int i = 0; i < moving_length; i++) {
        moving[i].x += dx;
    }
}

void horizon_move_object(Object* obj, Object& mario, int& level, int& max_lvl, int& score, 
                    Object*& brick, int& brick_length, Object*& moving, int& moving_length) {
    obj->x += obj->horiz_speed;

    for (int i = 0; i < brick_length; i++) {
        if (is_collision(*obj, brick[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    }
    if (obj->c_type == 'o') {
        Object tmp = *obj;
        vert_move_object(&tmp, mario, level, max_lvl, score, brick, brick_length, moving, moving_length);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void init_object(Object* obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
    set_object_pos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vert_speed = 0;
    obj->is_fly = false;
    obj->c_type = inType;
    obj->horiz_speed = 0.7;
}

bool is_collision(const Object& o1, const Object& o2) {
    return ((o1.x + o1.width) > o2.x ) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y ) && (o1.y < (o2.y + o2.height));
}

bool is_pos_in_map(int x, int y) {
    return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void mario_collision(Object& mario, int& max_lvl, int& level, int& score, 
    Object*& brick, int& brick_length, Object*& moving, int& moving_length) {
    for (int i = 0; i < moving_length; i++) {
        if (is_collision(mario, moving[i])) {
            if (moving[i].c_type == 'o') {
                if (mario.is_fly && (mario.vert_speed > 0) 
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                    score += 50;
                    delete_moving(i, moving, moving_length);
                    i--;
                    continue;
                } else {
                    player_dead(mario, max_lvl, level, score, brick, brick_length, moving, moving_length);
                }
            }
            if (moving[i].c_type == '$') {
                score += 100;
                delete_moving(i, moving, moving_length);
                i--;
                continue;
            }
        }
    }
}

void player_dead(Object& mario, int& max_lvl, int& level, int& score, 
    Object*& brick, int& brick_length, Object*& moving, int& moving_length) {
    system("color 4F");
    Sleep(500);
    create_level(mario, max_lvl, level, score, brick, brick_length, moving, moving_length);
}

void put_object_on_map (const Object& obj, char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int) round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (is_pos_in_map(i,j)) {
                map[j][i] = obj.c_type;
            }
        }
    }
}

void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], const int score) {
    char c[30];
    sprintf_s(c, "Score %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        map[1][i+5] = c[i];
    }
}

void set_cur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(Object* obj, float xPos, float yPos) {
    obj->x = xPos;
    obj->y = yPos;
}

void show_map(const char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        std::cout <<  map[j] << std::endl;
    }
}

void vert_move_object(Object* obj, Object& mario, int& level, int& max_lvl, int& score, 
    Object*& brick, int& brick_length, Object*& moving, int& moving_length) {
    obj->is_fly = true;
    obj->vert_speed += 0.25;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
    
    for (int i = 0; i < brick_length; i++) {
        if (is_collision (*obj, brick[i])) {
            if (obj->vert_speed > 0) {
                obj->is_fly = false;
            }

            if ((brick[i].c_type == '?') && (obj->vert_speed < 0) && (obj == &mario) ) {
                brick[i].c_type = '-';
                init_object(get_new_moving(moving, moving_length), brick[i].x, brick[i].y-3, 3, 2, '$');
                moving[moving_length-1].vert_speed = -0.3;
            }

            obj->y -= obj->vert_speed;
            obj->vert_speed = 0;
        
            if (brick[i].c_type == '+') {
                level++;
                if (level > max_lvl) level = 1;
                system("color 2F");
                Sleep(500);
                create_level(mario, max_lvl, level, score, brick, brick_length, moving, moving_length);
                
            }
            break;
        }
    }
}
