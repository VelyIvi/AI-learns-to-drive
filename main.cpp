#include <raylib.h>
#include <vector>
#include <iostream>

#include "map.hpp"
#include "car.hpp"
#include "pallete.h"

#define PI 3.14159265

Map* map = new Map();

Car* bestCar;
std::vector<Car> car;
std::vector<int> aliveCar;

int currentGeneration = 0;

long long simTime = 0;
long long currentSimTime = 0;
void startSim(){
//    std::cout<<"-STARTING SIMULATION-\n";

    car.clear();
    aliveCar.clear();
    for(int x = 0; x<100; x++){
        car.emplace_back(*map->startPos, *map->startRot, map->map_points, map->map_check);
        aliveCar.push_back(x);
    }
    bestCar = &car.at(0);
}
void retrySim(){
    currentGeneration++;
    currentSimTime = 0;
//    std::cout<<"-RETRYING SIMULATION-\n";
    for(int x = 0; x<car.size(); x++){
        aliveCar.push_back(x);
    }
    NeuralNetwork bestSavedNN = bestCar->nn;
    for(int i = 0; i<car.size(); i++){
//        if(i < car.size()/3*2) {
            car.at(i).nn = bestSavedNN;

            if (i != 0) {
                car.at(i).nn.Mutate(0.25f * float(float(i) / car.size()));
            }
//        } else {
//            car.at(i).nn.Randomize();
//        }
//        car.at(i).nn.Randomize();

        car.at(i).ResetValues(*map->startPos, *map->startRot, true);
    }

    bestCar = &car.at(0);

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
            car.at(aliveCar.at(i)).alive = false;
            return;

        }
    }


}
void GeneralInfo(){
    DrawText(TextFormat("%i", GetFPS()), 6, 6, 20, WallColor);
    DrawText(TextFormat("Current generation: %i", currentGeneration), 100, 6, 20, WHITE);
    DrawText(TextFormat("Fastest car laps: %i", bestCar->laps), 100, 30, 20, WHITE);

}

void Render(){
    BeginDrawing();
    ClearBackground(BackGroundColor);

    map->Draw();
    for(Car & cCar:car){
        if(&cCar == bestCar){
            cCar.DrawBest();

        } else {
            cCar.Draw();
        }
    }

    GeneralInfo();

    EndDrawing();
}

void smallRender(){
    BeginDrawing();
    ClearBackground(BLACK);
    GeneralInfo();

    EndDrawing();
}

void Startup(){
    SetWindowState(FLAG_VSYNC_HINT);
//    SetTargetFPS(60);

    map->Load_From_Json();

    InitWindow(1500, 800, "/C++/ Ai Learns To Drive - By Ivan Velychko");
    startSim();
    Render();

}

int main(){
    Startup();
    float delta;
    bool display = true;
    while (!WindowShouldClose())
    {
        delta = GetFrameTime();

        if(!display) {
            for(Car & cCar:car){
                cCar.Update(delta);
            }
            for(Car & cCar:car){
                cCar.Update(delta);
            }
            for(Car & cCar:car){
                cCar.Update(delta);
            }
            currentSimTime = currentSimTime + delta*3;
            simTime = simTime + delta*3;

        }else{
            for(Car & cCar:car){
                cCar.Update(delta);
                currentSimTime = currentSimTime + delta;
                simTime = simTime + delta;
            }
        }


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