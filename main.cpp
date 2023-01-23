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


Car* bestCar;
Car* selectedCar;

std::vector<Car> car;
std::vector<int> aliveCar;



int currentGeneration = 0;

float realTime = 0;
float simTime = 0;
float currentSimTime = 0;

float mutationValue = 0.25;

#include "simulationCommands.hpp"

void GeneralInfo(){
    info.DrawTextSim(TextFormat("FPS: %i", GetFPS()), 6, 6, 20, WallColor);
    info.DrawTextSim(TextFormat("Current generation: %i", currentGeneration), 6, 30, 20, WHITE);
    info.DrawTextSim(TextFormat("Fastest car laps: %i", bestCar->laps), 6, 54, 20, WHITE);
    info.DrawTextSim(TextFormat("Time total: %01.0f", realTime), 6, 78, 20, WHITE);
    info.DrawTextSim(TextFormat("Sim total time: %01.0f", simTime), 6, 102, 20, WHITE);
    info.DrawTextSim(TextFormat("Gen time: %01.0f", currentSimTime), 6, 126, 20, WHITE);
}
////UI Values
int CenteredCar = 0;
bool CenteredCarTyping = false;
bool CenterBest = true;
bool Pause = true;
bool Display = true;
bool ShowAll = true;


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
    ShowAll = GuiCheckBox((Rectangle){UI.margin+UI.position.x+115*UI.proc,UI.margin+UI.position.y+(float(12.5)+70)*UI.proc, 15*UI.proc, 15*UI.proc}, "Show all", ShowAll);

    mutationValue = GuiSliderBar((Rectangle){ UI.margin+UI.position.x+120*UI.proc, UI.margin+UI.position.y+5*UI.proc, 120*UI.proc, 30*UI.proc}, "Mutation", TextFormat("%0.2f", mutationValue), mutationValue, 0, 1.00);
    GuiSetStyle(SPINNER, STATE_DISABLED, true);

    if(!CenterBest)
        if (GuiSpinner((Rectangle){ UI.margin+UI.position.x+120*UI.proc,UI.margin+UI.position.y+40*UI.proc, 90*UI.proc, 15*UI.proc }, "Selected", &CenteredCar, 0, car.size() - 1, CenteredCarTyping)) CenteredCarTyping = !CenteredCarTyping;
    GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    CenterBest = GuiCheckBox((Rectangle){UI.margin + UI.position.x + 137 * UI.proc, UI.margin + UI.position.y + 55 * UI.proc, 15 * UI.proc, 15 * UI.proc }, "Select Best", CenterBest);

    DrawLineV({UI.margin+UI.position.x+5*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, WHITE);
//    DrawLineV({UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+145*UI.proc}, WHITE);
    DrawLineV({UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+5*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+145*UI.proc}, WHITE);

}

void Startup(){
//    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_MSAA_4X_HINT);


//    SetTargetFPS(60);

    map->Load_From_Json();

    InitWindow(1920, 1000, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    startSim();
}
void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);
//    sim->Update();
    Vector2 screenSize = Vector2{float(GetScreenWidth()), float(GetScreenHeight())};
    sim.Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.005)}, screenSize, Vector2{0.7,0.7});
    map->Draw(sim);

    for(Car & cCar:car){
        if (ShowAll) {
            if (CenterBest) {
                if (&cCar == bestCar) {
                    cCar.DrawBest(sim);
                } else if (&cCar == &car.at(0) && currentGeneration != 0) {
                    cCar.Draw(sim, GREEN, DARKGREEN);
                } else {
                    cCar.Draw(sim);
                }
            } else {
                if (&cCar == selectedCar) {
                    cCar.DrawBest(sim, YELLOW, true);
                } else if (&cCar == bestCar) {
                    cCar.DrawBest(sim, false);
                } else if (&cCar == &car.at(0) && currentGeneration != 0) {
                    cCar.Draw(sim, GREEN, DARKGREEN);
                } else {
                    cCar.Draw(sim);
                }
            }
        } else {
            if (CenterBest) {
                if (&cCar == bestCar) {
                    cCar.DrawBest(sim);
                }
            } else {
                if (&cCar == selectedCar) {
                    cCar.DrawBest(sim, YELLOW, true);
                } else if (&cCar == bestCar) {
                    cCar.DrawBest(sim, false);
                }
            }
        }
    }
//    info->Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.285});
    info.Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.71)}, screenSize, Vector2{0.285,0.28});
    nnInfo.Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.99});
    UI.Draw(Vector2{float(screenSize.x*0.295),float(screenSize.y*0.71)}, screenSize, Vector2{0.41,0.28});

    GeneralInfo();
    UIWindow();

    if(CenterBest)
        nnInfo.DrawNN(bestCar->nn);
    else
        nnInfo.DrawNN(selectedCar->nn);
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
    Render();
    float delta;
    while (!WindowShouldClose())
    {
        if(!CenterBest && CenteredCar < car.size()){
            selectedCar = &car.at(CenteredCar);
        }
        if(Pause) {
            delta = GetFrameTime();

            if (!Display) {
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }

            } else {
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }
            }
        }

        currentSimTime = currentSimTime + delta;
        simTime = simTime + delta;
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