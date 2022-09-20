#include <raylib.h>
#include <vector>
#include <string>


class Map{
    private:
        std::string name = "NoName";
    public:
        std::vector<std::vector<Vector2>> map_points = {};
        std::vector<Vector2> points = {{1,1}};
        Map(/* args */);
        ~Map();
};

Map::Map(/* args */){
}

Map::~Map(){
}
