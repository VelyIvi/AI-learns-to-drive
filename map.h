#include "nlohmann/json.hpp"
#include <fstream>
#include <string>


using json = nlohmann::json;


struct Map{
    private:
        std::string name = "no";
    public:
        std::vector<std::vector<Vector2>>* map_points = new std::vector<std::vector<Vector2>>;
        Map();
        ~Map();

        void Save_To_Json();

};

Map::Map(){

}

Map::~Map(){

}

void Map::Save_To_Json(){
    json j;
    int arrayXSize = 0;
    for(int x = 0; x < map_points->size(); x++){
        if (map_points->at(x).size() > arrayXSize){
            arrayXSize = map_points->at(x).size();
        }
    }
    float pointsee[map_points->size()][arrayXSize][2];

    for(int a = 0; a < map_points->size(); a++){
        for(int b = 0; b < map_points->at(a).size(); b++){
            pointsee[a][b][0] = map_points->at(a).at(b).x;
            pointsee[a][b][1] = map_points->at(a).at(b).y;
        }
    }
    std::cout<<pointsee<<"\n";
    // j["wall"] = pointsee;
    std::ofstream file(name+".json");
    file << j;
}
