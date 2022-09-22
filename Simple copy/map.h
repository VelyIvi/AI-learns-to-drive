#include <raylib.h>
#include <vector>
#include <string>


class Map{
    private:
        std::string name = "NoName";
    public:
        std::vector<std::vector<Vector2>> map_points = {};
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
