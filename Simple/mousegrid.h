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
        bool* edit;
        Map* m;
        ~MouseGrid();
        MouseGrid();
        void Update(int gridSize);
        void Draw();
};

MouseGrid::~MouseGrid(){
}

MouseGrid::MouseGrid(){
}

void MouseGrid::Update(int gridSize){
    real_position = GetMousePosition();
    if (IsKeyPressed(KEY_E)){
        if (*edit == true){
            *edit = false;
        }else if (*edit == false){
            *edit = true;
        }
    }
    if (*edit==false){
        return;
    }

    position = {round(real_position.x/gridSize)*gridSize, round(real_position.y/gridSize)*gridSize};
    int vecSize = m->points.size()-1;

    if(m->points.size() > 0){
        newestPoint = m->points.at(vecSize);
    }

    if(IsMouseButtonPressed(0)){
        if (position.x != newestPoint.x || position.y != newestPoint.y){
            m->points.push_back(position);
        }
    } else if(
        (IsMouseButtonPressed(1)||(IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyPressed(KEY_Z)))&&m->points.size()>0){
        m->points.pop_back();
        
    }

}

void MouseGrid::Draw(){
    DrawCircle(real_position.x, real_position.y, 2, RED);
    if (*edit==false){
        return;
    }
    if(m->points.size() > 0){
        DrawLineV(newestPoint, position, DARKGREEN);
        DrawCircle(newestPoint.x, newestPoint.y, 3.0f, GREEN);

    }
    DrawCircle(position.x, position.y, 3, YELLOW);

}