#include "mousegrid.h"

MouseGrid mouseGrid;

class Grid{
    private:
        const int gridSize = 20;
        std::vector<Vector2> DrawGridPoints;

    public:
        bool* edit = new bool(false);

        std::vector<std::vector<Vector2>>* map;
        Grid(std::vector<std::vector<Vector2>>* m);
        ~Grid();
        void Update();
        void Update_Components();
        void Draw();
        void Draw_Components();
        void AddPoint(Vector2 point);
};

Grid::Grid(std::vector<std::vector<Vector2>>* m){
    map = m;
    mouseGrid.map  = m;
    mouseGrid.edit = edit;
    Update();
    
}


Grid::~Grid(){
}

void Grid::Update(){
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    for (int i = 0; i < screenWidth; i+=gridSize){
            DrawGridPoints.push_back(Vector2{float(i), 0});
            DrawGridPoints.push_back(Vector2{float(i), float(screenHeight)});
    }
    for (int b = 0; b < screenHeight; b+=gridSize){
        DrawGridPoints.push_back(Vector2{0, float(b)});
        DrawGridPoints.push_back(Vector2{float(screenWidth), float(b)});
    }
}

void Grid::Update_Components(){
    mouseGrid.Update(gridSize);
}

void Grid::Draw(){
    for(int i = 0; i<DrawGridPoints.size(); i+=2){
        DrawLineV(DrawGridPoints.at(i), DrawGridPoints.at(i+1), DARKGRAY);
    }
}

void Grid::Draw_Components(){
    
    if (map->size()>0){
        for(int i=0; i<map->size(); i++){
            if (map->at(i).size()>0){
                for(int j=0; j<map->at(i).size()-1; j++){
                    if(i == mouseGrid.currentVec && *edit == true){
                        DrawLineV(map->at(i).at(j), map->at(i).at(j+1), GREEN);
                        DrawCircle(map->at(i).at(j).x, map->at(i).at(j).y, 2, GREEN);
                    }
                }
            }
        }
    }

    mouseGrid.Draw();
}

void Grid::AddPoint(Vector2 point){
}
