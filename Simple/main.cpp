#include <raylib.h> //build with "-lraylib"
#include <math.h>
#include <iostream>


#include "tank.h"
#include "grid.h"


Car car (Vector2{1500/2, 800/2});
Grid grid;

void Startup(){
    SetTargetFPS(60);
    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    HideCursor();
    grid.Update();
}

void Render(){
    BeginDrawing();
    ClearBackground(BLACK);
    grid.Draw();
    car.Draw();
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
        grid.Update_Components();
        Render();

    }
    return 0;
}