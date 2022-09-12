#include <raylib.h> //build with "-lraylib"
#include <iostream>
#include "car.h"

Car car (Vector2{1500/2, 800/2});

void Startup(){
    SetTargetFPS(180);
    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
}

void Render(){
    BeginDrawing();
    ClearBackground(BLACK);
    car.Draw();
    DrawFPS(10,10);
    EndDrawing();
}

int main(void){
    Startup();
    float delta;

    while (!WindowShouldClose())
    {
        delta = GetFrameTime();
        std::cout<<delta<<"\n";
        car.Update(delta);
        Render();

    }
    return 0;
}