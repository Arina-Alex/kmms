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

    bool Enemy::has_ground_ahead(const Vector<Brick>& bricks) const {
        float ahead_x = (get_horiz_speed() > 0)
            ? x() + get_width() + 1
            : x() - 1;
        float check_y = y() + get_height() + 1; 

        for (int i = 0; i < bricks.get_size(); ++i) {
            const Brick& brick = bricks[i];
            if (ahead_x >= brick.x() &&
                ahead_x <= brick.x() + brick.get_width() &&
                check_y >= brick.y() &&
                check_y <= brick.y() + brick.get_height()) {
                return true;
            }
        }
        return false;
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
        apply_gravity(); 
        move();
    }
}