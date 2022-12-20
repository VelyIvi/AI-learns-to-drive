#include <raylib.h>
#include <vector>
#include <iostream>

#include <random>

#include "map.hpp"
#include "tank.hpp"
#include "pallete.h"

#define PI 3.14159265

Map* map = new Map();

Car car(*map->startPos, *map->startRot, map->map_points);

void Startup(){
    SetTargetFPS(60);
//    map->Load_From_Json();

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
}

void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);

    map->Draw();
    car.Draw();

    DrawText(TextFormat("%i", GetFPS()), 6, 6, 20, WallColor);
    EndDrawing();
}

int main(){
    Startup();
    float delta;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();

        car.Update(delta);

        if(IsKeyDown(KEY_Q)){
            map->Save_To_Json();
        }

        Render();

    }

    delete map;
    map = nullptr;
    std::cout<<"Main code finished\n";

    return 0;
}