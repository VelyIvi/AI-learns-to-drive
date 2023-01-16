#include <raylib.h> //build with "-lraylib"

#include "canvas.h"
#include "car.h"
#include "ui.h"

Canvas * canvas = new Canvas();
Car car;

Canvas simulation (0, Vector2{1500, 800});

void Startup(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1800, 900, "/C++/ Ai Learns To Drive - By Ivan Velychko");

    

    int display = GetCurrentMonitor();
    

    // ToggleFullscreen();
}

void Render(){
    BeginDrawing();
    ClearBackground(DARKGRAY);
    // car.Draw();

    simulation.Draw(Vector2{float(GetScreenWidth()*0.03), float(GetScreenHeight()*0.05)}, Vector2{float(GetScreenWidth()), float(GetScreenHeight())}, Vector2{0.7, 0.7});
    DrawFPS(10,10);
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