#include <raylib.h>

class MouseGrid {
    private:
        Vector2 real_position;
        Vector2 position;

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
    if(IsMouseButtonPressed(0)){
        MapPoints.push_back(position);
    } else if(IsMouseButtonPressed(1)&&MapPoints.size()>0){
        MapPoints.pop_back();
    }

}

void MouseGrid::Draw(){
    DrawCircle(real_position.x, real_position.y, 2, RED);
    DrawCircle(position.x, position.y, 5, YELLOW);
}