#include <raylib.h>
#include <vector>
#include <string>


class Map{
    private:
        std::string name = "NoName";
    public:
        std::vector<std::vector<Vector2>> map_points = {};
        std::vector<Vector2> points = {{10,10},{1000,10},{1000,700},{10,700},{10,10}};
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
