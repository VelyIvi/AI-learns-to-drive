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

        void Draw();

        void Save_To_Json();
        void Load_From_Json();
};

Map::Map(){
    Load_From_Json();
}

Map::~Map(){
    std::cout<<"Called Map destructor\n";

    delete map_points;
    map_points = NULL;

    delete map_check;
    map_check = NULL;

}


void drawArrayMapPoints(std::vector<std::vector<Vector2>>* vec, Color color){
    if (vec->size()>0){
        for(int i=0; i<vec->size(); i++){
            if (vec->at(i).size()>0){
                for(int j=0; j<vec->at(i).size()-1; j++){
                    DrawLineV(vec->at(i).at(j), vec->at(i).at(j+1), color);
                    // DrawCircle(map_points->at(i).at(j).x, map_points->at(i).at(j).y, 1, color);
                }
            }
        }
    }
}

void Map::Draw(){
    drawArrayMapPoints(map_points, WallColor);
    drawArrayMapPoints(map_check, CheckColor);
}


void Map::Save_To_Json(){
    std::cout<<"Saving to json"<<"\n";
    json j;

    time_t now = time(0);
    char* dt = ctime(&now);


    auto lines = json{
        {"check", json::array()},
        {"wall", json::array()},
        {"posX", int()},
        {"posY", int()},
        {"rot", float()},
    };

    for (int i = 0; i < map_points->size(); i++) {
        auto& outer = lines["wall"];
        for (int j = 0; j < map_points->at(i).size(); j++) {
            outer[i].push_back({map_points->at(i).at(j).x, map_points->at(i).at(j).y});
        }
    }

    for (int i = 0; i < map_check->size(); i++) {
        auto& outer = lines["check"];
        for (int j = 0; j < map_check->at(i).size(); j++) {
            outer[i].push_back({map_check->at(i).at(j).x, map_check->at(i).at(j).y});
        }
    }

    lines["posX"] = startPos->x;
    lines["posY"] = startPos->y;
    lines["rot"] = *startRot;


    std::ofstream file(name + ".json");
    file << lines;
}

void Map::Load_From_Json(){
    std::cout<<"Loading from json"<<"\n";
    map_points->clear();
    map_check->clear();

    std::ifstream f("map.json");
    json data = json::parse(f);
//    std::cout<<data["posX"]<<"\n";
//    std::cout<<data["posY"]<<"\n";
//    std::cout<<data["wall"].at(1).size()<<"\n";
//    std::cout<<"e--e--e--e--e--e\n";

    *startPos={data["posX"], data["posY"]};
    *startRot = data["rot"];

    for(int w1 = 0; w1<data["wall"].size(); w1++){
        if(map_points->size() < w1+1){map_points->push_back({});};
        for(int w2 = 0; w2<data["wall"].at(w1).size(); w2++){
            map_points->at(w1).push_back(Vector2{data["wall"].at(w1).at(w2).at(0), data["wall"].at(w1).at(w2).at(1)});
        }
    }

    for(int w1 = 0; w1<data["check"].size(); w1++){
        if(map_check->size() < w1+1){map_check->push_back({});};
        for(int w2 = 0; w2<data["check"].at(w1).size(); w2++){
            map_check->at(w1).push_back(Vector2{data["check"].at(w1).at(w2).at(0), data["check"].at(w1).at(w2).at(1)});
        }
    }

    f.close();
}