#include "mousegrid.h"

MouseGrid mouseGrid;

class Grid{
    private:
        const int gridSize = 20;
        std::vector<Vector2> DrawGridPoints;

    public:
        bool* edit = new bool(false);

        std::vector<std::vector<Vector2>>* map;
        std::vector<Vector4>* check;

        Vector2 startPos= {0,0};
        float startRot= 0;


        Grid(std::vector<std::vector<Vector2>>* w, std::vector<Vector4>* c);
        ~Grid();
        void Update();
        void Update_Components();
        void Draw();
        void Draw_Components();
};

Grid::Grid(std::vector<std::vector<Vector2>>* w, std::vector<Vector4>* c){
    map = w;
    check = c;
    mouseGrid.wall  = w;
    mouseGrid.check  = c;
    // mouseGrid.map = m;

    mouseGrid.edit = edit;
    Update();
    
}


Grid::~Grid(){
    // mouseGrid.~MouseGrid();


    // delete edit;
    // edit = NULL;


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
        DrawLineV(DrawGridPoints.at(i), DrawGridPoints.at(i+1), GridColor);
    }
}

void Grid::Draw_Components(){
    mouseGrid.Draw();
}

