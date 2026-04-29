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
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

void clear_map () {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = '.';
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

void init_object(TObject *obj, float xPos, float yPos, float oWidth, float oHeight) {
    set_object_pos(obj,xPos,yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vert_speed = 0;
}

void vert_move_object(TObject *obj) {
    (*obj).vert_speed += 0.05;
    set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);

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
            // if (is_pos_in_map(i,j)){
                map[j][i] = '@';
            // }
        }
    }
}

void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int main() {
    init_object(&mario, 39, 10, 3, 3);

    do {
        clear_map();
        vert_move_object(&mario);
        put_object_on_map(mario);

        setCur(0, 0);
        show_map();

        Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
    
    return 0;
}