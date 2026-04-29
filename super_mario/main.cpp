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
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brick_length;

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
}

bool is_collision(TObject o1, TObject o2);

void vert_move_object(TObject *obj) {
    (*obj).is_fly = true;
    (*obj).vert_speed += 0.15;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);
    
    for (int i = 0; i < brick_length; i ++) {
        if (is_collision (*obj, brick[i])) {
        (*obj).y -= (*obj).vert_speed;
        (*obj).vert_speed = 0;
        (*obj).is_fly = false;
        break;
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
    for (int i = ix; i < (ix + iWidth);i++){
        for (int j = iy; j < (iy + iHeight);j++){
            if (is_pos_in_map(i,j)){
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
}

bool is_collision(TObject o1, TObject o2) {
    return ((o1.x + o1.width) > o2.x ) && (o1.x < (o2.x + o2.width)) &&
        ((o1.y + o1.height) > o2.y ) && (o1.y < (o2.y + o2.height));
}

void create_level() {
    init_object(&mario, 39, 10, 3, 3, '@');

    brick_length = 5;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brick_length);
    init_object(brick+0, 20, 20, 40, 5, '#');
    init_object(brick+1, 60, 15, 10, 10, '#');
    init_object(brick+2, 80, 20, 20, 5, '#');
    init_object(brick+3, 120, 15, 10, 10, '#');
    init_object(brick+4, 150, 20, 40, 5, '#');
}

int main() {
    create_level();

    do {
        clear_map();

        if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) mario.vert_speed = -1.5;
        if (GetKeyState('A') < 0) horizon_move_map(2);
        if (GetKeyState('D') < 0) horizon_move_map(-2);

        if (mario.y > mapHeight) create_level();

        vert_move_object(&mario);
        for (int i = 0; i < brick_length; i++) {
            put_object_on_map(brick[i]);
        }
        
        put_object_on_map(mario);

        setCur(0, 0);
        show_map();

        Sleep(10);
    }

    while (GetKeyState(VK_ESCAPE) >= 0);
    
    return 0;
}