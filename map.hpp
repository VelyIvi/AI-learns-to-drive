#include "nlohmann/json.hpp"
#include "pallete.h"

#include <fstream>
#include <string>

//#include <ctime>

using json = nlohmann::json;


struct Map{
    private:
        std::string name = "map";
    public:
        std::vector<std::vector<Vector2>>* map_points = new std::vector<std::vector<Vector2>>;
        std::vector<std::vector<Vector2>>* map_check = new std::vector<std::vector<Vector2>>;
        Vector2* startPos = new Vector2({0,0});
        float* startRot = new float(0);
        Map();
        ~Map();

        void Draw() const;
        void Draw(Simulation& canvas);


        void Save_To_Json();
        void Load_From_Json() const;

};

void drawArrayMapPoints(std::vector<std::vector<Vector2>> *const pVector, Color color, Simulation simulation);

Map::Map(){
}

Map::~Map(){
    std::cout<<"Called Map destructor\n";

    delete map_points;
    map_points = nullptr;

    delete map_check;
    map_check = nullptr;

}


void drawArrayMapPoints(std::vector<std::vector<Vector2>>* vec, Color color){
    if (!vec->empty()){
        for(auto & i : *vec){
            if (!i.empty()){
                for(int j=0; j<i.size()-1; j++){
                    DrawLineV(i.at(j), i.at(j+1), color);
                    // DrawCircle(map_points->at(i).at(j).x, map_points->at(i).at(j).y, 1, color);
                }
            }
        }
    }
}

void Map::Draw() const{
    drawArrayMapPoints(map_points, WallColor);
    drawArrayMapPoints(map_check, CheckColor);
}
void Map::Draw(Simulation& canvas){
    drawArrayMapPoints(map_points, WallColor, canvas);
    drawArrayMapPoints(map_check, CheckColor, canvas);
}

void drawArrayMapPoints(std::vector<std::vector<Vector2>> *const vec, Color color, Simulation canvas) {
    if (!vec->empty()){
        for(auto & i : *vec){
            if (!i.empty()){
                for(int j=0; j<i.size()-1; j++){
                    canvas.DrawLineVSim(i.at(j), i.at(j+1), color);
                    // DrawCircle(map_points->at(i).at(j).x, map_points->at(i).at(j).y, 1, color);
                }
            }
        }
    }
}


void Map::Save_To_Json(){
    std::cout<<"Saving to json"<<"\n";
    json j;

//    time_t now = time(0);
//    char* dt = ctime(&now);


    auto lines = json{
        {"check", json::array()},
        {"wall", json::array()},
        {"posX", int()},
        {"posY", int()},
        {"rot", float()},
    };

    for (int mapOuter = 0; mapOuter < map_points->size(); mapOuter++) {
        auto& outer = lines["wall"];
        for (int mapInner = 0; mapInner < map_points->at(mapOuter).size(); mapInner++) {
            outer[mapOuter].push_back({map_points->at(mapOuter).at(mapInner).x, map_points->at(mapOuter).at(mapInner).y});
        }
    }

    for (int checkOuter = 0; checkOuter < map_check->size(); checkOuter++) {
        auto& outer = lines["check"];
        for (int checkInner = 0; checkInner < map_check->at(checkOuter).size(); checkInner++) {
            outer[checkOuter].push_back({map_check->at(checkOuter).at(checkInner).x, map_check->at(checkOuter).at(checkInner).y});
        }
    }

    lines["posX"] = startPos->x;
    lines["posY"] = startPos->y;
    lines["rot"] = *startRot;


    std::ofstream file(name + ".json");
    file << lines;
}

void Map::Load_From_Json() const{
    std::cout<<"Loading from json"<<"\n";
    map_points->clear();
    map_check->clear();

    std::ifstream f("map.json");
    json data = json::parse(f);

    *startPos={data["posX"], data["posY"]};
    *startRot = data["rot"];

    for(int w1 = 0; w1<data["wall"].size(); w1++){
        if(map_points->size() < w1+1){map_points->push_back({});}
        for(int w2 = 0; w2<data["wall"].at(w1).size(); w2++){
            map_points->at(w1).push_back(Vector2{data["wall"].at(w1).at(w2).at(0), data["wall"].at(w1).at(w2).at(1)});
        }
    }

    for(int w1 = 0; w1<data["check"].size(); w1++){
        if(map_check->size() < w1+1){map_check->push_back({});}
        for(int w2 = 0; w2<data["check"].at(w1).size(); w2++){
            map_check->at(w1).push_back(Vector2{data["check"].at(w1).at(w2).at(0), data["check"].at(w1).at(w2).at(1)});
        }
    }

    f.close();
}