#include <raylib.h> //build with "-lraylib"

#include "car.h"

Car car;

void Startup(){
    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
}

void Render(){
    BeginDrawing();
    ClearBackground(DARKGRAY);
    car.Draw();

    EndDrawing();
}

int main(void){
    Startup();

    while (!WindowShouldClose())
    {
        Render();
    }
    return 0;
}