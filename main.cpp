#include "src/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"


#include <vector>
#include <iostream>
#include "pallete.h"
#include "ColorMixer.hpp"
#include <random>
#include "utils.hpp"
#include <algorithm>
#include "network.hpp"

#include "simulation.hpp"
#include "car.hpp"
#include "map.hpp"



//#define PI 3.14159265

Map* map = new Map();
Vector2 simSize = {1500,800};
Simulation sim(simSize);

Vector2 genInfoSize = {300,150};
Simulation info(genInfoSize);

Vector2 nnInfoSize = {550,1000};
Simulation nnInfo(nnInfoSize);

Vector2 UISize = {450,150};
Simulation UI(UISize);

Car car(*map->startPos, *map->startRot, map->map_points, map->map_check);


int currentGeneration = 0;

float realTime = 0;
float simTime = 0;
float currentSimTime = 0;

float learningRate = 0.25;
float discountRate = 0.25;
float epsilon = 0.1;




void retrySim(){
    currentGeneration++;
    currentSimTime = 0;
    car.nn.Randomize();
    car.ResetValues(*map->startPos, *map->startRot, true);


}

void startSim(){
    currentGeneration = 0;
    realTime = 0;
    simTime = 0;
    currentSimTime = 0;

    car.ResetValues(*map->startPos, *map->startRot, true);
    car.nn.Randomize();
}

void ResetGen(){
    currentSimTime = 0;
    car.ResetValues(*map->startPos, *map->startRot, true);
}
void CheckSim(){
    if(!car.alive){
        ResetGen();
    }
}


void GeneralInfo(){
    info.DrawTextSim(TextFormat("FPS: %i", GetFPS()), 6, 6, 20, WallColor);
    info.DrawTextSim(TextFormat("Current generation: %i", currentGeneration), 6, 30, 20, WHITE);
    info.DrawTextSim(TextFormat("Fastest car laps: %i", car.laps), 6, 54, 20, WHITE);
    info.DrawTextSim(TextFormat("Time total: %01.0f", realTime), 6, 78, 20, WHITE);
    info.DrawTextSim(TextFormat("Sim total time: %01.0f", simTime), 6, 102, 20, WHITE);
    info.DrawTextSim(TextFormat("Gen time: %01.0f", currentSimTime), 6, 126, 20, WHITE);
}
////UI Values
bool Pause = true;
bool Display = true;

void UIWindow(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 12*UI.proc);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
//    GuiSetStyle(, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

//    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+5*UI.proc, 60*UI.proc, 30*UI.proc}, "Start Game")) {
//        std::cout<<"button :>\n";
//    }
    Pause = GuiCheckBox((Rectangle){UI.margin+UI.position.x+45*UI.proc,UI.margin+UI.position.y+float(12.5)*UI.proc, 15*UI.proc, 15*UI.proc}, "Update", Pause);
    Display = GuiCheckBox((Rectangle){UI.margin+UI.position.x+45*UI.proc,UI.margin+UI.position.y+(float(12.5)+35)*UI.proc, 15*UI.proc, 15*UI.proc}, "Display", Display);

    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+80*UI.proc, 60*UI.proc, 20*UI.proc}, "Full Reset")) {
        startSim();
    }
    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+105*UI.proc, 60*UI.proc, 40*UI.proc}, "Reset Gen")) {
        ResetGen();
    }


    //layer2
    car.learningRate = GuiSliderBar((Rectangle){UI.margin + UI.position.x + 160 * UI.proc, UI.margin + UI.position.y + 5 * UI.proc, 120 * UI.proc, 30 * UI.proc}, "Learning rate: ", TextFormat("%0.2f", car.learningRate), car.learningRate, 0, 1.00);
    discountRate = GuiSliderBar((Rectangle){UI.margin + UI.position.x + 160 * UI.proc, UI.margin + UI.position.y + 40 * UI.proc, 120 * UI.proc, 30 * UI.proc}, "Discount rate: ", TextFormat("%0.2f", discountRate), discountRate, 0, 1.00);
    discountRate = GuiSliderBar((Rectangle){UI.margin + UI.position.x + 160 * UI.proc, UI.margin + UI.position.y + 75 * UI.proc, 120 * UI.proc, 30 * UI.proc}, "Epsilon: ", TextFormat("%0.2f", discountRate), discountRate, 0, 1.00);



    GuiSetStyle(SPINNER, STATE_DISABLED, true);

    GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

    DrawLineV({UI.margin+UI.position.x+5*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, WHITE);
//    DrawLineV({UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+145*UI.proc}, WHITE);
    DrawLineV({UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+5*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+145*UI.proc}, WHITE);

}

void Startup(){
//    SetWindowState(FLAG_FULLSCREEN_MODE);
    Vector2 windowSize = {1920, 1000};
    SetWindowState(FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowSize.x, windowSize.y, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    map->Load_From_Json();

}
void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);
//    sim->Update();
    Vector2 screenSize = Vector2{float(GetScreenWidth()), float(GetScreenHeight())};
    sim.Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.005)}, screenSize, Vector2{0.7,0.7});
    map->Draw(sim);

    car.DrawBest(sim);
//    info->Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.285});
    info.Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.71)}, screenSize, Vector2{0.285,0.28});
    nnInfo.Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.99});
    UI.Draw(Vector2{float(screenSize.x*0.295),float(screenSize.y*0.71)}, screenSize, Vector2{0.41,0.28});

    GeneralInfo();
    UIWindow();

    nnInfo.DrawNN(car.nn);
    EndDrawing();
}

void smallRender(){
    BeginDrawing();
    ClearBackground(BLACK);
    Vector2 screenSize = Vector2{float(GetScreenWidth()), float(GetScreenHeight())};
//    sim->Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.005)}, screenSize, Vector2{0.8,0.8});

    GeneralInfo();
    UIWindow();
    EndDrawing();
}



int main(){

    Startup();

    startSim();
    Render();

    float delta;
    while (!WindowShouldClose())
    {

        if(Pause) {
            delta = GetFrameTime();
            car.Update(delta);
            currentSimTime = currentSimTime + delta;
            simTime = simTime + delta;
        }

        realTime = realTime + delta;

        if(!Display) {
            smallRender();
        }else{
            Render();
        }
        CheckSim();

        if(IsKeyPressed(KEY_SPACE))
            Pause = !Pause;
    }

    delete map;
    map = nullptr;
    std::cout<<"Main code finished\n";

    return 0;
}