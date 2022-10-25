#include <raylib.h>
#include <math.h>
#include <vector>
#include <iostream>


#include "map.h"
#include "tank.h"
#include "grid.h"
#include "pallete.h"

Map map;


Car car (map.startPos, map.startRot);
// std::cout>>map.startPos>>"\n";
Grid grid (map.map_points, map.map_check);


const bool GridEnabled = true;
const bool EditEnabled = false;

void Startup(){
    SetTargetFPS(60);

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    if(GridEnabled){grid.Update();}
}

void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);
    if(GridEnabled){grid.Draw();}
    
    map.Draw();
    car.Draw();

    if(EditEnabled){grid.Draw_Components();}
    DrawText(TextFormat("%i", GetFPS()), 10, 10, 20, GREEN);
    EndDrawing();
}

int main(){
    Startup();
    float delta;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();
        car.Update(float(1.0/60.0));

        if(EditEnabled){grid.Update_Components();}
        Render();

    }

    // grid.~Grid();

    car.~Car();


    // map.~Map();
    // delete map;
    // map = NULL;


    return 0;
}