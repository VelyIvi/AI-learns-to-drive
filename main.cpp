#include <raylib.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "map.h"
#include "tank.h"
#include "grid.h"
#include "pallete.h"


#define PI 3.14159265

Map* map = new Map();

Car car (map->startPos, map->startRot, map->map_points);
Grid grid (map->map_points, map->map_check);

const bool GridEnabled = true;
const bool EditEnabled = true;

void Startup(){
    SetTargetFPS(60);

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    if(GridEnabled){grid.Update();}
}

void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);
    if(GridEnabled){grid.Draw();}
    
    map->Draw();
    car.Draw();

    if(EditEnabled){grid.Draw_Components();}
    DrawText(TextFormat("%i", GetFPS()), 10, 10, 20, GREEN);
    EndDrawing();
}

int main(){
    Startup();
    float delta;
    car.Update(float(1.0/60.0));

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();

        car.Update(delta);

        if(IsKeyDown(KEY_Q)){
            map->Save_To_Json();
        }

        if(EditEnabled){grid.Update_Components();}
        Render();

    }

    delete map;
    map = NULL;
    std::cout<<"Main code finished\n";

    return 0;
}