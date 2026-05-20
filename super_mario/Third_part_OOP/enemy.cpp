#include "brick.hpp"
#include "constants.hpp"
#include "enemy.hpp"

namespace mal {
    Enemy::Enemy(float x, float y) : Moving(3, 2, TYPE_ENEMY, ENEMY_SPEED) {
        setX(x);
        setY(y);
        is_fly = false;
        vert_speed = 0;
    }

    char Enemy::get_symbol() const {
        return 'o';
    }

    bool Enemy::has_ground_under(const Vector<Brick>& bricks) const {
        float checkY = y() + get_height() + 1;
        
        for (int i = 0; i < bricks.get_size(); ++i) {
            const Brick& brick = bricks[i];
            
            if (x() + get_width() > brick.x() && 
                x() < brick.x() + brick.get_width() &&
                checkY >= brick.y() && 
                checkY < brick.y() + 5) {
                return true;
            }
        }
        return false;
    }

    void Enemy::update() {
        move();
    }
}