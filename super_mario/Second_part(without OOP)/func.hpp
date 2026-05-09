#ifndef FUNC_HPP
#define FUNC_HPP

#include <cmath>
#include <cstring>
#include <iostream>
#include <windows.h>

#define MAP_HEIGHT 25
#define MAP_WIDTH 80


struct Object
{
    float x;
    float y;
    float height;
    float width;
    float vert_speed;
    float horiz_speed;
    bool is_fly;
    char c_type;
};

void clear_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]);

void create_level(Object& mario, int& max_lvl, int& level, int& score,
                  Object*& brick, int& brick_length,
                  Object*& moving, int& moving_length);

void delete_moving(int i, Object*& moving, int& moving_length);
Object* get_new_brick(Object*& brick, int& brick_length);
Object* get_new_moving(Object*& moving, int& moving_length);

void horizon_move_map(float dx, Object& mario, 
                    Object*& brick, int& brick_length,
                      Object*& moving, int& moving_length);

void horizon_move_object(Object* obj, Object& mario, int& level, int& max_lvl,
                         int& score, Object*& brick, int& brick_length,
                         Object*& moving, int& moving_length);

void init_object(Object* obj, float xPos, float yPos, float oWidth,
                 float oHeight, char inType);

bool is_collision(const Object& o1, const Object& o2);
bool is_pos_in_map(int x, int y);

void mario_collision(Object& mario, int& max_lvl, int& level, int& score,
                     Object*& brick, int& brick_length,
                     Object*& moving, int& moving_length);

void player_dead(Object& mario, int& max_lvl, int& level, int& score,
                 Object*& brick, int& brick_length,
                 Object*& moving, int& moving_length);

void put_object_on_map(const Object& obj, char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], int score);
void set_cur(int x, int y);
void set_object_pos(Object* obj, float xPos, float yPos);
void show_map(const char map[MAP_HEIGHT][MAP_WIDTH + 1]);

void vert_move_object(Object* obj, Object& mario, int& level, int& max_lvl,
                      int& score, Object*& brick, int& brick_length,
                      Object*& moving, int& moving_length);

#endif 