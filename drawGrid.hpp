#include "mouseGrid.hpp"


class Grid{
    MouseGrid mouseGrid;
private:
    const int gridSize = 20;
    std::vector<Vector2> DrawGridPoints;
public:
    Grid(std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>>* c, Vector2* p, float* r);
    ~Grid();
    void Update();
    void Update_Components();
    void Draw();
    void Draw_Components();
};

Grid::Grid(std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>>* c, Vector2* p, float* r) : mouseGrid(w, c, p, r){
    Update();
}


Grid::~Grid() {
    std::cout << "Called Grid destructor\n";
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

