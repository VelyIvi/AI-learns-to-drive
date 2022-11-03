#include "nlohmann/json.hpp"
#include "pallete.h"

#include <fstream>
#include <string>

#include <ctime>

using json = nlohmann::json;


struct Map{
    private:
        std::string name = "map";
    public:
        std::vector<std::vector<Vector2>>* map_points = new std::vector<std::vector<Vector2>>;
        std::vector<Vector4>* map_check = new std::vector<Vector4>;
        Vector2 startPos = {180,400};
        float startRot = -95;
        Map();
        ~Map();

        void Draw();

        void Save_To_Json();
        void Load_From_Json();
};

Map::Map(){
    map_points->push_back({{Vector2{240.0,120.0},Vector2{120.0,240.0},Vector2{100.0,500.0},Vector2{200.0,640.0},Vector2{300.0,720.0},Vector2{480.0,700.0},Vector2{540.0,600.0},Vector2{580.0,540.0},Vector2{600.0,440.0},Vector2{600.0,360.0},Vector2{520.0,340.0},Vector2{500.0,300.0},Vector2{560.0,280.0},Vector2{660.0,300.0},Vector2{700.0,420.0},Vector2{700.0,580.0},Vector2{740.0,720.0},Vector2{900.0,740.0},Vector2{1060.0,740.0},Vector2{1260.0,660.0},Vector2{1380.0,560.0},Vector2{1480.0,440.0},Vector2{1480.0,340.0},Vector2{1420.0,220.0},Vector2{1320.0,160.0},Vector2{1160.0,120.0},Vector2{1080.0,180.0},Vector2{1040.0,300.0},Vector2{1020.0,400.0},Vector2{980.0,440.0},Vector2{920.0,440.0},Vector2{900.0,380.0},Vector2{880.0,320.0},Vector2{880.0,220.0},Vector2{860.0,120.0},Vector2{780.0,100.0},Vector2{520.0,100.0},Vector2{240.0,120.0}}});
    map_points->push_back({{Vector2{320.0,200.0},Vector2{240.0,380.0},Vector2{280.0,560.0},Vector2{340.0,600.0},Vector2{480.0,520.0},Vector2{520.0,420.0},Vector2{440.0,380.0},Vector2{400.0,300.0},Vector2{460.0,240.0},Vector2{560.0,220.0},Vector2{700.0,240.0},Vector2{740.0,300.0},Vector2{760.0,420.0},Vector2{840.0,560.0},Vector2{960.0,660.0},Vector2{1120.0,640.0},Vector2{1180.0,580.0},Vector2{1260.0,520.0},Vector2{1360.0,480.0},Vector2{1400.0,380.0},Vector2{1320.0,280.0},Vector2{1220.0,220.0},Vector2{1140.0,240.0},Vector2{1120.0,440.0},Vector2{1040.0,520.0},Vector2{940.0,520.0},Vector2{840.0,460.0},Vector2{820.0,340.0},Vector2{800.0,240.0},Vector2{760.0,180.0},Vector2{680.0,180.0},Vector2{560.0,160.0},Vector2{400.0,180.0},Vector2{320.0,200.0}}});
    
}

Map::~Map(){
    std::cout<<"Called Map destructor\n";

    delete map_points;
    map_points = NULL;

    delete map_check;
    map_check = NULL;

}

void Map::Draw(){
    if (map_points->size()>0){
        for(int i=0; i<map_points->size(); i++){
            if (map_points->at(i).size()>0){
                for(int j=0; j<map_points->at(i).size()-1; j++){
                    DrawLineV(map_points->at(i).at(j), map_points->at(i).at(j+1), WallColor);
                    // DrawCircle(map_points->at(i).at(j).x, map_points->at(i).at(j).y, 1, BLUE);
                }
            }
        }
    }

    if (map_check->size()>0){
        for(int e=0; e<map_check->size(); e++){
            DrawLineV(Vector2{map_check->at(e).x, map_check->at(e).y}, Vector2{map_check->at(e).z, map_check->at(e).w}, YELLOW);
        }
    }
}

void Map::Save_To_Json(){
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
    // auto car = json{
    //     {"posX", int()},
    //     {"posY", int()},
    //     {"rot", float()},
    // };

    for (int i = 0; i < map_points->size(); i++) {
        auto& outer = lines["wall"];
        for (int j = 0; j < map_points->at(i).size(); j++) {
            outer[i].push_back({map_points->at(i).at(j).x, map_points->at(i).at(j).y});
        }
    }

    // for (int r = 0; r < map_check->size(); r++) {
    //     auto& outer = lines["check"];
    //     outer[r].push_back({map_check->at(r).x, map_check->at(r).y, map_check->at(r).z, map_check->at(r).w});
    // }

    lines["posX"] = startPos.x;
    lines["posY"] = startPos.y;
    lines["rot"] = startRot;
    

    std::ofstream file(name + ".json");
    file << lines;
    // file << car;

}

void Map::Load_From_Json(){
    map_points->clear();
    map_check->clear();

    std::ifstream file("map.json");

    json j = json::parse(file);
    
    // for (int i = 0; i < lines[wall]->size(); i++) {
    //     // auto& outer = lines["wall"];
    //     // for (int j = 0; j < map_points->at(i).size(); j++) {
    //     //     outer[i].push_back({map_points->at(i).at(j).x, map_points->at(i).at(j).y});
    //     // }
    // }

    // map_points->push_back(j[wall]);    
}