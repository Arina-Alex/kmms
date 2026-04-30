#include <cstdio>
#include <cstdlib>

#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
    float x, y;
    float width, height;
    float vert_speed;
    bool is_fly;
    char c_type;
    float horiz_speed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brick_length;

TObject *moving = NULL;
int moving_length;

int level = 1;
int score;
int max_lvl;

void clear_map () {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        sprintf (map[j], map[0]);
    }
}

void show_map() {
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        printf("%s", map[j]);
    }
}

void set_object_pos(TObject *obj, float xPos, float yPos) {
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void init_object(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
    set_object_pos(obj,xPos,yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vert_speed = 0;
    (*obj).c_type = inType;
    (*obj).horiz_speed = 1.5;
}

bool is_collision(TObject o1, TObject o2);
void create_level(int lvl);
TObject *get_new_moving();
void player_dead();

void vert_move_object(TObject *obj) {
    (*obj).is_fly = true;
    (*obj).vert_speed += 0.25;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);
    
    for (int i = 0; i < brick_length; i ++) {
        if (is_collision (*obj, brick[i])) {
            if (obj[0].vert_speed > 0) {
                (*obj).is_fly = false;
            }

            if ((brick[i].c_type == '?') && (obj[0].vert_speed < 0) && (obj == &mario) ) {
                brick[i].c_type = '-';
                init_object(get_new_moving(), brick[i].x, brick[i].y-3, 3, 2, '$');
                moving[moving_length-1].vert_speed = -0.5;
            }

            (*obj).y -= (*obj).vert_speed;
            (*obj).vert_speed = 0;
        
            if (brick[i].c_type == '+') {
                level++;
                if (level > max_lvl) level = 1;
                system("color 2F");
                Sleep(500);
                create_level(level);
                
            }
            break;
        }
    }
}

void delete_moving(int i) {
    moving_length--;
    moving[i] = moving[moving_length];
    moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
}

void mario_collision() {
    for (int i = 0; i < moving_length; i++) {
        if (is_collision(mario, moving[i])) {
            if (moving[i].c_type == 'o') {
                if (mario.is_fly && (mario.vert_speed > 0) 
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                    score += 50;
                    delete_moving(i);
                    i--;
                    continue;
                } else {
                    player_dead();
                }
            }
            if (moving[i].c_type == '$') {
                score += 100;
                delete_moving(i);
                i--;
                continue;
            }
        }
    }
}

void horizon_move_object(TObject *obj) {
    obj[0].x += obj[0].horiz_speed;

    for (int i = 0; i < brick_length; i++) {
        if (is_collision(obj[0], brick[i])) {
            obj[0].x -= obj[0].horiz_speed;
            obj[0].horiz_speed = -obj[0].horiz_speed;
            return;
        }
    }
    if (obj[0].c_type == 'o') {
        TObject tmp = *obj;
        vert_move_object(&tmp);
        if (tmp.is_fly == true) {
            obj[0].x -= obj[0].horiz_speed;
            obj[0].horiz_speed = -obj[0].horiz_speed;
        }
    }

}


bool is_pos_in_map(int x, int y) {
    return ( (x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight) );
}

void put_object_on_map (TObject obj) {
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

void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void horizon_move_map(float dx) {
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

void player_dead() {
    system("color 4F");
    Sleep(500);
    create_level(level);
}

bool is_collision(TObject o1, TObject o2) {
    return ((o1.x + o1.width) > o2.x ) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y ) && (o1.y < (o2.y + o2.height));
}

TObject *get_new_brick() {
    brick_length++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
    return brick + brick_length - 1;
}

TObject *get_new_moving() {
    moving_length++;
    moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
    return moving + moving_length - 1;
}

void put_score_on_map() {
    char c[30];
    sprintf(c, "Score %d", score);
    int len = strlen(c);
    for (int i = 0; i < len;i++) {
        map[1][i+5] = c[i];
    }
}

void create_level(int lvl) {
    system("color 3D");

    brick_length = 0;
    brick = (TObject*)realloc(brick, 0);
    moving_length = 0;
    moving = (TObject*)realloc(moving, 0);


    init_object(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (lvl == 1) {
        brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
            init_object(get_new_brick(), 30, 10, 5, 3, '?');
            init_object(get_new_brick(), 50, 10, 5, 3, '?');
        init_object(get_new_brick(), 60, 15, 40, 10, '#');
            init_object(get_new_brick(), 60, 5, 10, 3, '-');
            init_object(get_new_brick(), 70, 5, 5, 3, '?');
            init_object(get_new_brick(), 75, 5, 5, 3, '-');
            init_object(get_new_brick(), 80, 5, 5, 3, '?');
            init_object(get_new_brick(), 85, 5, 10, 3, '-');
        init_object(get_new_brick(), 100, 20, 20, 5, '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5, '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');
    
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
    }

    if (lvl == 2) {
        brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
        init_object(get_new_brick(), 60, 15, 10, 10, '#');
        init_object(get_new_brick(), 80, 20, 20, 5, '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5, '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');

        moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 65, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(), 175, 10, 3, 2, 'o');
    }

    if (lvl == 3) {
        brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
        init_object(get_new_brick(), 80, 20, 15, 10, '#');
        init_object(get_new_brick(), 120, 15, 15, 10, '#');
        init_object(get_new_brick(), 160, 10, 15, 15, '+');

        moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 50, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 90, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 130, 10, 3, 2, 'o');    
    }
    max_lvl = 3;
    
}

int main() {
    create_level(level);

    do {
        clear_map();

        if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) mario.vert_speed = -2.2;
        if (GetKeyState('A') < 0) horizon_move_map(2);
        if (GetKeyState('D') < 0) horizon_move_map(-2);

        if (mario.y > mapHeight) player_dead();

        vert_move_object(&mario);
        mario_collision();

        for (int i = 0; i < brick_length; i++) {
            put_object_on_map(brick[i]);
        }

        for (int i = 0; i < moving_length; i++) {
            vert_move_object(moving + i);
            horizon_move_object(moving + i);
            if (moving[i].y > mapHeight) {
                delete_moving(i);
                i--;
                continue;
            }
            put_object_on_map(moving[i]);
        }
        
        put_object_on_map(mario);
        put_score_on_map();

        setCur(0, 0);
        show_map();

        Sleep(10);
    }

    while (GetKeyState(VK_ESCAPE) >= 0);
    
    return 0;
}