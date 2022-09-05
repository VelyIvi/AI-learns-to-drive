#include <raylib.h> //build with "-lraylib"

#include "canvas.h"
#include "car.h"
#include "ui.h"

Car car;

Canvas menu (1);
Canvas simulation (10);
// Canvas nn (10);


void Startup(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1800, 900, "/C++/ Ai Learns To Drive - By Ivan Velychko");

    

    int display = GetCurrentMonitor();
    

    // ToggleFullscreen();
}

void Render(){
    BeginDrawing();
    ClearBackground(DARKGRAY);
    car.Draw();
    menu.Draw(Vector2{10, 10}, Vector2{float(GetScreenWidth()), float(GetScreenHeight())}, Vector2{1, 0.03});

    // simulation.Draw(Vector2{0, 10}, Vector2{float(GetScreenWidth()), float(GetScreenHeight())}, Vector2{0.7, 0.7});

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