#include <vector>
#include <raylib.h>

#include "mousegrid.h"

MouseGrid mouseGrid;

class Grid{
    private:
        const int gridSize = 10;
        std::vector<Vector2> DrawGridPoints;
        std::vector<Vector2> MapPoints;

    public:
        Grid(std::vector<Vector2> nDrawGridPoints);
        ~Grid();
        void Update();
        void Update_Components();
        void Draw();
        void Draw_Components();
        void AddPoint(Vector2 point);
};

Grid::Grid(std::vector<Vector2> nDrawGridPoints){
    MapPoints = nDrawGridPoints;
    mouseGrid.MapPoints=nDrawGridPoints;
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
    
    // if (mouseGrid.MapPoints.size()>=2){
    //     for(int i=0; i<mouseGrid.MapPoints.size()-1; i++){
    //         DrawLineV(mouseGrid.MapPoints.at(i), mouseGrid.MapPoints.at(i+1), GREEN);
    //     }
    // }

    // if (mouseGrid.MapPoints.size()>0){
    //     Vector2 lastPoint = mouseGrid.MapPoints.at(mouseGrid.MapPoints.size()-1);
    //     DrawCircle(lastPoint.x, lastPoint.y, 3.0f, GREEN);
    // }

    mouseGrid.Draw();
}

void Grid::AddPoint(Vector2 point){
}
