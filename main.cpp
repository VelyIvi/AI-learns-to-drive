#include <raylib.h> //build with "-lraylib"

#include "canvas.h"
#include "car.h"
#include "ui.h"

Car car;
Canvas canvas;

void Startup(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");

    

    int display = GetCurrentMonitor();
    

    // ToggleFullscreen();
}

void Render(){
    BeginDrawing();
    ClearBackground(DARKGRAY);
    car.Draw();
    canvas.XReduction(1500);
    canvas.Draw();
    DrawRectangle(0, 800, 100, 10, WHITE);
    DrawRectangle(0, 0, 100, 10, WHITE);


    EndDrawing();

}

int main(void){
    Startup();


    while (!WindowShouldClose())
    {
        Render();
    }
    if(IsWindowFullscreen())    ToggleFullscreen();
    return 0;
}