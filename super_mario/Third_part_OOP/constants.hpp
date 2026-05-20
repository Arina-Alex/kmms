#pragma once

namespace mal {

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 25;

enum ObjectType {
    TYPE_PLAYER = '@',
    TYPE_PLATFORM = '#',
    TYPE_BONUS = '?',
    TYPE_EMPTY_BONUS = '-',
    TYPE_ENEMY = 'o',
    TYPE_MONEY = '$',
    TYPE_GOAL = '+',
    TYPE_AIR = ' '
};

const float GRAVITY = 0.05f;
const float JUMP_POWER = -1.5f;
const float ENEMY_SPEED = 0.7f;

} 
