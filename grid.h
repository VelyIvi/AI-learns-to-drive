#include "mousegrid.h"

MouseGrid mouseGrid;

class Grid{
    private:
        const int gridSize = 20;
        std::vector<Vector2> DrawGridPoints;

    public:
        bool* edit = new bool(false);
        Map* m;
        Grid(Map* map);
        ~Grid();
        void Update();
        void Update_Components();
        void Draw();
        void Draw_Components();
        void AddPoint(Vector2 point);
};

Grid::Grid(Map* map){
    m = map;
    mouseGrid.m  = map;
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
    
    if (m->map_points.size()>0){
        for(int i=0; i<m->map_points.size(); i++){
            if (m->map_points.at(i).size()>0){
                for(int j=0; j<m->map_points.at(i).size()-1; j++){
                    if(i == mouseGrid.currentVec && *edit == true){
                        DrawLineV(m->map_points.at(i).at(j), m->map_points.at(i).at(j+1), GREEN);
                    } else {
                        DrawLineV(m->map_points.at(i).at(j), m->map_points.at(i).at(j+1), BLUE);
                    }
                }
            }
        }
    }

    mouseGrid.Draw();
}

void Grid::AddPoint(Vector2 point){
}
