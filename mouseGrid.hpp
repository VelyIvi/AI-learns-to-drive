#include <raylib.h>

//#define DARKYELLOW  (Color){177, 174, 0, 255}

class MouseGrid {
private:
    Vector2 real_position;
    Vector2 position;
    Vector2 newestPoint;

    int currentVecWall;
    int currentVecCheck;

    std::vector<std::vector<Vector2>>* wall;
    std::vector<std::vector<Vector2>>* check;
    Vector2* carPosition;
    float* carRotation;
    const Vector2 carSize = {20,12};
    Rectangle carRec() {
        return Rectangle{carPosition->x, carPosition->y, carSize.x, carSize.y};
    }


    std::vector<std::string> types = {"WALL", "CHECK", "CAR"};
    int currentType = 0;

public:
    ~MouseGrid();
    MouseGrid(std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>>* c, Vector2* p, float* r);
    void Update(int gridSize);
    void Draw();

    void drawSelectedArrayMapPoints(std::vector<std::vector<Vector2>>* vec, int currentVec, Color col, Color shadeCol);
    void MapVecPointsEdit(std::vector<std::vector<Vector2>>* vec, int* currentVec, int gridSize);
    void CarEdit(Vector2* pos, float* rot);

};

MouseGrid::~MouseGrid(){
    std::cout<<"Called MouseEdit destructor\n";
}

MouseGrid::MouseGrid(std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>>* c, Vector2* p, float* r){
    wall = w;
    check = c;
    carPosition = p;
    carRotation = r;
}


void MouseGrid::MapVecPointsEdit(std::vector<std::vector<Vector2>>* vec, int* currentVec, int gridSize){
    if(vec->size()>1){
        if(IsKeyPressed(KEY_L)){
            *currentVec = *currentVec+1;
            std::cout<<*currentVec<<"\n";
            if(*currentVec>vec->size()-1){
                *currentVec = 0;
            }
        }
//        currentVec = 1;

        if(IsKeyPressed(KEY_J)){
            *currentVec = *currentVec-1;
            std::cout<<*currentVec<<"\n";
            if(*currentVec<0){
                *currentVec = vec->size()-1;
            }
        }
    }

    if(*currentVec>vec->size()-1){
        *currentVec = 0;
    }
    if(*currentVec<0){
        *currentVec = vec->size()-1;
    }


    if (IsKeyPressed(KEY_K)){
        if (!vec->empty()){
            for(int h = 0 ; h<=vec->size()-1; h++){
                if (vec->at(h).size()==0){
                    *currentVec = h;
                    return;
                }
            }
        }

        vec->push_back({});
        if (vec->size()>1){
            *currentVec = vec->size()-1;
        }
    }

    if(vec->empty()){
        return;
    }

    if (vec->at(*currentVec).empty()){
        if(IsMouseButtonPressed(0)){
            vec->at(*currentVec).push_back(position);
            int vecSize = vec->at(*currentVec).size()-1;
            newestPoint = vec->at(*currentVec).at(vecSize);
        }
        else if(IsMouseButtonPressed(1)){
            vec->erase(vec->begin() + *currentVec);
            if(*currentVec<0){
                *currentVec = vec->size()-1+0;
            }
            if(*currentVec>vec->size()-1){
                *currentVec = 0;
            }
        }
        return;
    }
    int vecSize = vec->at(*currentVec).size()-1;
    newestPoint = vec->at (*currentVec).at(vecSize);

    if(IsMouseButtonPressed(0)){
        if (position.x != newestPoint.x || position.y != newestPoint.y){
            vec->at (*currentVec).push_back(position);
        }
    } else if(IsMouseButtonPressed(1)){
        vec->at (*currentVec).pop_back();
    }
}

void MouseGrid::CarEdit(Vector2* pos, float* rot){
    float delta = GetFrameTime();
    if(IsMouseButtonPressed(0)){
        *carPosition = position;
    }
    if(IsKeyDown(KEY_RIGHT)){
        *carRotation+=100*delta;
    }
    if(IsKeyDown(KEY_LEFT)){
        *carRotation-=100*delta;
    }
}

void MouseGrid::Update(int gridSize){
    real_position = GetMousePosition();
    position = {round(real_position.x/gridSize)*gridSize, round(real_position.y/gridSize)*gridSize};

    if (IsKeyPressed(KEY_Z)){
        currentType = 0;
    } else if (IsKeyPressed(KEY_X)){
        currentType = 1;
    } else if (IsKeyPressed(KEY_C)){
        currentType = 2;
    }

    if (types.at(currentType) == "WALL"){
        int* ptr = &currentVecWall;
        MapVecPointsEdit(wall, ptr, gridSize);
    } else if(types.at(currentType) == "CHECK"){
        int* ptr = &currentVecCheck;
        MapVecPointsEdit(check, ptr, gridSize);
    } else if(types.at(currentType) == "CAR") {
        CarEdit(carPosition, carRotation);
    } else {
        if (currentType>types.size()-1){
            currentType = types.size()-1;
        } else if(currentType<0){
            currentType = 0;
        }
    }
}

void MouseGrid::drawSelectedArrayMapPoints(std::vector<std::vector<Vector2>>* vec, int currentVec, Color col, Color shadeCol){
    if (vec->size()>0){
        for(int i=0; i<vec->size(); i++){
            if (vec->at(i).size()>0){
                for(int j=0; j<vec->at(i).size()-1; j++){
                    if(i == currentVec){
                        DrawLineV(vec->at(i).at(j), vec->at(i).at(j+1), col);
                        DrawCircle(vec->at(i).at(j).x, vec->at(i).at(j).y, 2, col);
                    }
                }
            }
        }
    }


    if (vec->size()>0){
        if(vec->at(currentVec).size() > 0){
            DrawLineV(newestPoint, position, shadeCol);
            DrawCircle(newestPoint.x, newestPoint.y, 3.0f, col);
        }
        DrawCircle(position.x, position.y, 3, shadeCol);
        const char *cur_vec_text = TextFormat("%i", currentVec);
        DrawText(cur_vec_text, 10, 40, 40, col);
    } else {
        DrawText("There are no points, press \"K\" to draw a new point!", 800, 50, 20, YELLOW);
    }
}


void MouseGrid::Draw(){
    DrawCircle(real_position.x, real_position.y, 3, MAROON);

    if (types.at(currentType) == "WALL"){
        drawSelectedArrayMapPoints(wall, currentVecWall, PURPLE, DARKPURPLE);
    } else if(types.at(currentType) == "CHECK"){
        drawSelectedArrayMapPoints(check, currentVecCheck, GREEN, DARKGREEN);
    } else if (types.at(currentType) == "CAR"){
        DrawCircle(position.x, position.y, 3, BLUE);
    }

    DrawText(types.at(currentType).c_str(), 800, 10, 30, YELLOW);
    DrawRectanglePro(carRec(), Vector2{carSize.x/2, carSize.y/2}, *carRotation, CarColor);
    DrawLineV(*carPosition ,{float(cos(-(*carRotation)*PI/180.0)*carSize.x/2+carPosition->x), float(sin(-(*carRotation)*PI/180.0)*-carSize.x/2+carPosition->y)}, BLACK);
}