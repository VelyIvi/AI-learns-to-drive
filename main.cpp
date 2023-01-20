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

Vector2 nnInfoSize = {500,600};
Simulation nnInfo(nnInfoSize);

Vector2 UISize = {450,150};
Simulation UI(UISize);


Car* bestCar;
std::vector<Car> car;
std::vector<int> aliveCar;

int currentGeneration = 0;

float realTime = 0;
float simTime = 0;
float currentSimTime = 0;


float mutationValue = 0.25;


void startSim(){
    car.clear();
    aliveCar.clear();

    currentGeneration = 0;
    realTime = 0;
    simTime = 0;
    currentSimTime = 0;

    for(int x = 0; x<100; x++){
        car.emplace_back(*map->startPos, *map->startRot, map->map_points, map->map_check);
        aliveCar.push_back(x);
    }
    bestCar = &car.at(0);
}
void retrySim(){
    float mut = mutationValue;
    currentGeneration++;
    currentSimTime = 0;
    for(int x = 0; x<car.size(); x++){
        aliveCar.push_back(x);
    }
    NeuralNetwork bestSavedNN = bestCar->nn;
    for(int i = 0; i<car.size(); i++){
//        if(i < car.size()/3*2) {
            car.at(i).nn = bestSavedNN;

            if (i != 0) {
                car.at(i).nn.Mutate(mut * float(float(i) / car.size()));
            }
//        } else {
//            car.at(i).nn.Randomize();
//        }
//        car.at(i).nn.Randomize();

        car.at(i).ResetValues(*map->startPos, *map->startRot, true);
    }

    bestCar = &car.at(0);

}

void ResetGen(){
    aliveCar.clear();
    currentSimTime = 0;
    for(int x = 0; x<car.size(); x++){
        aliveCar.push_back(x);
        car.at(x).ResetValues(*map->startPos, *map->startRot, true);
    }
}


void CheckSim(){
    if(aliveCar.empty()){
        retrySim();
        return;
    }
    for(int i = 0; i < aliveCar.size(); i++){
        if(car.at(aliveCar.at(i)).points > bestCar->points){
            bestCar = &car.at(aliveCar.at(i));
        }
        if(!car.at(aliveCar.at(i)).alive){
            aliveCar.erase(aliveCar.begin()+i);
            return;
        } else if(car.at(aliveCar.at(i)).laps>=3){
            aliveCar.erase(aliveCar.begin()+i);
            retrySim();
//            car.at(aliveCar.at(i)).alive = false; ////crash
            return;

        }
    }


}
void GeneralInfo(){
    info.DrawTextSim(TextFormat("FPS: %i", GetFPS()), 6, 6, 20, WallColor);
    info.DrawTextSim(TextFormat("Current generation: %i", currentGeneration), 6, 30, 20, WHITE);
    info.DrawTextSim(TextFormat("Fastest car laps: %i", bestCar->laps), 6, 54, 20, WHITE);
    info.DrawTextSim(TextFormat("Time total: %01.0f", realTime), 6, 78, 20, WHITE);
    info.DrawTextSim(TextFormat("Sim total time: %01.0f", simTime), 6, 102, 20, WHITE);
    info.DrawTextSim(TextFormat("Gen time: %01.0f", currentSimTime), 6, 126, 20, WHITE);
}
int CenteredCar = 0;
bool CenteredCarTyping = false;
bool CenterBest = true;
bool Pause = true;
void UIWindow(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 12*UI.proc);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
//    GuiSetStyle(, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

//    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+5*UI.proc, 60*UI.proc, 30*UI.proc}, "Start Game")) {
//        std::cout<<"button :>\n";
//    }
    Pause = GuiCheckBox((Rectangle){UI.margin+UI.position.x+50*UI.proc,UI.margin+UI.position.y+float(12.5)*UI.proc, 15*UI.proc, 15*UI.proc}, "Update", Pause);

    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+40*UI.proc, 60*UI.proc, 30*UI.proc}, "Start Game")) {
        std::cout<<"button :>\n";
    }
    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+80*UI.proc, 60*UI.proc, 20*UI.proc}, "Full Reset")) {
        startSim();
    }
    if (GuiButton((Rectangle){ UI.margin+UI.position.x+5*UI.proc,UI.margin+UI.position.y+105*UI.proc, 60*UI.proc, 40*UI.proc}, "Reset Gen")) {
        ResetGen();
    }


    //layer2
    if (GuiButton((Rectangle){ UI.margin+UI.position.x+70*UI.proc,UI.margin+UI.position.y+80*UI.proc, 60*UI.proc, 20*UI.proc}, "Full Reset")) {
        startSim();
    }
//    if (GuiButton((Rectangle){ UI.margin+UI.position.x+70*UI.proc,UI.margin+UI.position.y+105*UI.proc, 60*UI.proc, 15*UI.proc}, "Full Reset")) {
//        startSim();
//    }
//    if (GuiButton((Rectangle){ UI.margin+UI.position.x+70*UI.proc,UI.margin+UI.position.y+130*UI.proc, 60*UI.proc, 15*UI.proc}, "Full Reset")) {
//        startSim();
//    }

    mutationValue = GuiSliderBar((Rectangle){ UI.margin+UI.position.x+120*UI.proc, UI.margin+UI.position.y+5*UI.proc, 120*UI.proc, 30*UI.proc}, "Mutation", TextFormat("%0.2f", mutationValue), mutationValue, 0, 1.00);
    GuiSetStyle(SPINNER, STATE_DISABLED, true);

    if(!CenterBest)
        if (GuiSpinner((Rectangle){ UI.margin+UI.position.x+120*UI.proc,UI.margin+UI.position.y+40*UI.proc, 90*UI.proc, 15*UI.proc }, "Selected", &CenteredCar, 0, car.size() - 1, CenteredCarTyping)) CenteredCarTyping = !CenteredCarTyping;
    GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    CenterBest = GuiCheckBox((Rectangle){UI.margin + UI.position.x + 137 * UI.proc, UI.margin + UI.position.y + 55 * UI.proc, 15 * UI.proc, 15 * UI.proc }, "Select Best", CenterBest);

    DrawLineV({UI.margin+UI.position.x+5*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, WHITE);
    DrawLineV({UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+77*UI.proc}, {UI.margin+UI.position.x+67*UI.proc, UI.margin+UI.position.y+145*UI.proc}, WHITE);

}

void Startup(){

    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

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
        if(&cCar == bestCar){
            cCar.DrawBest(sim);
        } else if(&cCar == &car.at(0) && currentGeneration!=0) {
            cCar.Draw(sim, GREEN,DARKGREEN);
        }else{
            cCar.Draw(sim);
        }
    }
//    info->Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.285});
    info.Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.71)}, screenSize, Vector2{0.285,0.28});
    nnInfo.Draw(Vector2{float(screenSize.x*0.71),float(screenSize.y*0.005)}, screenSize, Vector2{0.285,0.985});
    UI.Draw(Vector2{float(screenSize.x*0.295),float(screenSize.y*0.71)}, screenSize, Vector2{0.41,0.28});

    GeneralInfo();
    UIWindow();

    nnInfo.DrawNN(bestCar->nn);
    EndDrawing();
}

void smallRender(){
    BeginDrawing();
    ClearBackground(BLACK);
    Vector2 screenSize = Vector2{float(GetScreenWidth()), float(GetScreenHeight())};
//    sim->Draw(Vector2{float(screenSize.x*0.005),float(screenSize.y*0.005)}, screenSize, Vector2{0.8,0.8});

    GeneralInfo();
    EndDrawing();
}



int main(){
    Startup();
    Render();
    float delta;
    bool display = true;
    while (!WindowShouldClose())
    {
        if(Pause) {
            delta = GetFrameTime();

            if (!display) {
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }
                currentSimTime = currentSimTime + delta * 3;
                simTime = simTime + delta * 3;

            } else {
                for (Car &cCar: car) {
                    cCar.Update(delta);
                }
                currentSimTime = currentSimTime + delta;
                simTime = simTime + delta;

            }
        }

        realTime = realTime + delta;

        if(!display) {
            smallRender();
        }else{
            Render();
        }
        CheckSim();

        if(IsKeyPressed(KEY_SPACE)){
            display = !display;
        }
    }

    delete map;
    map = nullptr;
    std::cout<<"Main code finished\n";

    return 0;
}