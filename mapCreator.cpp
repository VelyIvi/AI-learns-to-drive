#include <raylib.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "map.hpp"
#include "drawGrid.hpp"
#include "pallete.h"


#define PI 3.14159265

Map* map = new Map();

Grid grid (map->map_points, map->map_check, map->startPos, map->startRot);

void Startup(){
    SetTargetFPS(60);

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    grid.Update();
}

void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);
    grid.Draw();
    HideCursor();

    map->Draw();

    grid.Draw_Components();
    DrawText(TextFormat("%i", GetFPS()), 10, 10, 20, GREEN);
    EndDrawing();
}

int main(){
    Startup();
    float delta;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();

        if(IsKeyPressed(KEY_Q)){
            map->Save_To_Json();
        }

        if(IsKeyPressed(KEY_W)){
            map->Load_From_Json();
        }

        grid.Update_Components();
        Render();

    }

    delete map;
    map = NULL;
    std::cout<<"Main code finished\n";

    return 0;
}