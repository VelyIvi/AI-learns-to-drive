#include "nlohmann/json.hpp"
#include <fstream>
#include <string>

#include <ctime>

using json = nlohmann::json;


struct Map{
    private:
        std::string name = "Untitled";
    public:
        std::vector<std::vector<Vector2>>* map_points = new std::vector<std::vector<Vector2>>;
        // map_points = {{{240.0,120.0},{120.0,240.0},{100.0,500.0},{200.0,640.0},{300.0,720.0},{480.0,700.0},{540.0,600.0},{580.0,540.0},{600.0,440.0},{600.0,360.0},{520.0,340.0},{500.0,300.0},{560.0,280.0},{660.0,300.0},{700.0,420.0},{700.0,580.0},{740.0,720.0},{900.0,740.0},{1060.0,740.0},{1260.0,660.0},{1380.0,560.0},{1480.0,440.0},{1480.0,340.0},{1420.0,220.0},{1320.0,160.0},{1160.0,120.0},{1080.0,180.0},{1040.0,300.0},{1020.0,400.0},{980.0,440.0},{920.0,440.0},{900.0,380.0},{880.0,320.0},{880.0,220.0},{860.0,120.0},{780.0,100.0},{520.0,100.0},{240.0,120.0}},{{320.0,200.0},{240.0,380.0},{280.0,560.0},{340.0,600.0},{480.0,520.0},{520.0,420.0},{440.0,380.0},{400.0,300.0},{460.0,240.0},{560.0,220.0},{700.0,240.0},{740.0,300.0},{760.0,420.0},{840.0,560.0},{960.0,660.0},{1120.0,640.0},{1180.0,580.0},{1260.0,520.0},{1360.0,480.0},{1400.0,380.0},{1320.0,280.0},{1220.0,220.0},{1140.0,240.0},{1120.0,440.0},{1040.0,520.0},{940.0,520.0},{840.0,460.0},{820.0,340.0},{800.0,240.0},{760.0,180.0},{680.0,180.0},{560.0,160.0},{400.0,180.0},{320.0,200.0}}};
        Map();
        ~Map();

        void Draw();

        void Save_To_Json();
        void Load_From_Json();
};

Map::Map(){

}

Map::~Map(){

}

void Map::Draw(){
    if (map_points->size()>0){
        for(int i=0; i<map_points->size(); i++){
            if (map_points->at(i).size()>0){
                for(int j=0; j<map_points->at(i).size()-1; j++){
                    DrawLineV(map_points->at(i).at(j), map_points->at(i).at(j+1), BLUE);
                    DrawCircle(map_points->at(i).at(j).x, map_points->at(i).at(j).y, 2, BLUE);
                }
            }
        }
    }
}

void Map::Save_To_Json(){
    json j;

    time_t now = time(0);
    char* dt = ctime(&now);


    auto result = json{
        {"item", json::array()},
    };

    for (int i = 0; i < map_points->size(); i++) {
        auto& outer = result["item"];
        for (int j = 0; j < map_points->at(i).size(); j++) {
            outer[i].push_back({map_points->at(i).at(j).x, map_points->at(i).at(j).y});
        }
    }

    std::ofstream file(name + dt + ".json");
    file << result;
}

void Map::Load_From_Json(){

}