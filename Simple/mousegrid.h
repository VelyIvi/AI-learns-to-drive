#include <raylib.h>
#include <iostream>
#include <vector>

#include <math.h>



class MouseGrid {
    private:
        Vector2 real_position;
        Vector2 position;
        Vector2 newestPoint;
    public:
        ~MouseGrid();
        MouseGrid();
        void Update(int gridSize);
        void Draw();
        std::vector<Vector2> MapPoints;
};

MouseGrid::~MouseGrid(){
}

MouseGrid::MouseGrid(){
}

void MouseGrid::Update(int gridSize){
    real_position = GetMousePosition();
    position = {round(real_position.x/gridSize)*gridSize, round(real_position.y/gridSize)*gridSize};
    int vecSize = MapPoints.size()-1;

    if(MapPoints.size() > 0){
        newestPoint = MapPoints.at(vecSize);
    }

    if(IsMouseButtonPressed(0)){
        if (position.x != newestPoint.x || position.y != newestPoint.y){
            MapPoints.push_back(position);
        }
    } else if(
        (IsMouseButtonPressed(1)||(IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyPressed(KEY_Z)))&&MapPoints.size()>0){
        MapPoints.pop_back();
        
    }

}

void MouseGrid::Draw(){
    if(MapPoints.size() > 0){
        DrawLineV(newestPoint, position, DARKGREEN);
    }

    DrawCircle(real_position.x, real_position.y, 2, RED);
    DrawCircle(position.x, position.y, 4, YELLOW);
}