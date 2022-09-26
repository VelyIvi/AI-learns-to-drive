#include "raylib.h"
    //build with "-lraylib"
//g++ -o main main.cpp -lraylib && ./main
#include <math.h>
#include <vector>
#include <iostream>


#include "map.h"
#include "tank.h"
#include "grid.h"
#include "utils.h"

Map* map = new Map;


Car car (Vector2{1500/2, 800/2});
Grid grid (map->map_points);

void Startup(){
    SetTargetFPS(60);

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    grid.Update();
}

void Render(){
    BeginDrawing();
    ClearBackground(BLACK);
    grid.Draw();
    car.Draw();
    map->Draw();
    grid.Draw_Components();
    DrawFPS(10,10);
    EndDrawing();
}

int main(void){
    Startup();
    float delta;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();
        car.Update(delta);
        if (IsKeyPressed(KEY_A)){
            map->Save_To_Json();
        }
        grid.Update_Components();
        Render();

    }
    return 0;
}