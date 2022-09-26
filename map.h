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

    time_t now = time(0);
    char* dt = ctime(&now);


    auto result = json{
        {"item", json::array()},
    };

    for (int i = 0; i < map_points->size(); i++) {
        auto& outer = result["item"];
        for (int j = 0; j < map_points->at(i).size(); j++) {
            // You'll need to convert whatever Items is into a JSON type first
            outer[i].push_back({map_points->at(i).at(j).x, map_points->at(i).at(j).y});
        }
    }

    std::ofstream file(name + dt + ".json");
    file << result;
}
