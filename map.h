#include "nlohmann/json.hpp"

using json = nlohmann::json;

json j;

struct Map{
    private:
        // string name = "NoName";
    public:
        std::vector<std::vector<Vector2>>* map_points = new std::vector<std::vector<Vector2>>;
        Map();
        ~Map();

        // void Map::Save_To_Json();
};

Map::Map(){

}

Map::~Map(){

}

// void Map::Save_To_Json(){

// }
