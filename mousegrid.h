#include <raylib.h>

//#define DARKYELLOW  (Color){177, 174, 0, 255}

class MouseGrid {
    private:
        Vector2 real_position;
        Vector2 position;
        Vector2 newestPoint;

        int currentVecWall = 0;
        int currentVecCheck = 0;

    public:
        bool* edit;
        std::vector<std::vector<Vector2>>* wall;
        std::vector<Vector4>* check;


        std::vector<std::string> types = {"WALL", "CHECK", "CAR"};
        std::string currentType = "WALL";

        ~MouseGrid();
        MouseGrid();
        void Update(int gridSize);
        void Draw();
};

MouseGrid::~MouseGrid(){
    std::cout<<"Called MouseEdit destructor\n";
}

MouseGrid::MouseGrid(){

}

void MouseGrid::Update(int gridSize){
    real_position = GetMousePosition();


    // if (IsKeyPressed(KEY_A)){
    //     map->Save_To_Json();
    // }

    // if (IsKeyPressed(KEY_S)){
    //     map->Load_From_Json();
    // }


    if (IsKeyPressed(KEY_E)){
        if (*edit == true){
            *edit = false;
        }else if (*edit == false){
            *edit = true;
        }
    }
    if (*edit==false){
        ShowCursor();
        return;
    }

    HideCursor();

    if (IsKeyPressed(KEY_Z)){
        currentType = types.at(0);
    } else if (IsKeyPressed(KEY_X)){
        currentType = types.at(1);
    } else if (IsKeyPressed(KEY_C)){
        currentType = types.at(2);
    }

    if (currentType == "WALL"){
        if(wall->size()>1){
            if(IsKeyPressed(KEY_L)){
                currentVecWall++;
                if(currentVecWall>wall->size()-1){
                    currentVecWall = 0;
                }
            }
            if(IsKeyPressed(KEY_J)){
                currentVecWall--;
                if(currentVecWall<0){
                    currentVecWall = wall->size()-1;
                }
            }
        }
        
        if(currentVecWall>wall->size()-1){
            currentVecWall = 0;
        }
        if(currentVecWall<0){
                currentVecWall = wall->size()-1;
        }
        

        if (IsKeyPressed(KEY_K)){
            if (wall->size()>0){
                for(int h = 0 ; h<=wall->size()-1; h++){
                    if (wall->at(h).size()==0){
                        currentVecWall = h;
                        return;
                    }
                }
            }

            wall->push_back({});
            if (wall->size()>1){
                currentVecWall = wall->size()-1;
            }
        }

        position = {round(real_position.x/gridSize)*gridSize, round(real_position.y/gridSize)*gridSize};
        if(wall->size() < 1){
            return;
        }

        if (wall->at(currentVecWall).size() < 1){
            if(IsMouseButtonPressed(0)){
                wall->at(currentVecWall).push_back(position);
                int vecSize = wall->at(currentVecWall).size()-1;
                newestPoint = wall->at(currentVecWall).at(vecSize);
            }
            else if(IsMouseButtonPressed(1)){
                wall->erase(wall->begin() + currentVecWall);
                if(currentVecWall<0){
                    currentVecWall = wall->size()-1+0;
                }
                if(currentVecWall>wall->size()-1){
                    currentVecWall = 0;
                }
            }
        return;
        }
        int vecSize = wall->at(currentVecWall).size()-1;
        newestPoint = wall->at(currentVecWall).at(vecSize);

        if(IsMouseButtonPressed(0)){
            if (position.x != newestPoint.x || position.y != newestPoint.y){
                wall->at(currentVecWall).push_back(position);
            }
        } else if(IsMouseButtonPressed(1)){        
            wall->at(currentVecWall).pop_back(); 
        }
    } else if(currentType == "CHECK"){
        
    } else if(currentType == "CAR") {

    } else {
        currentType = "WALL";
    }




}

void MouseGrid::Draw(){
    if (*edit==false){
        return;
    }
    
    DrawCircle(real_position.x, real_position.y, 3, MAROON);

    if (currentType == "WALL"){
        if (wall->size()>0){
            for(int i=0; i<wall->size(); i++){
                if (wall->at(i).size()>0){
                    for(int j=0; j<wall->at(i).size()-1; j++){
                        if(i == currentVecWall && *edit == true){
                            DrawLineV(wall->at(i).at(j), wall->at(i).at(j+1), GREEN);
                            DrawCircle(wall->at(i).at(j).x, wall->at(i).at(j).y, 2, GREEN);
                        }
                    }
                }
            }
        }

        if (wall->size()<=0){
            return;
        }
        if(wall->at(currentVecWall).size() > 0){
            DrawLineV(newestPoint, position, DARKGREEN);
            DrawCircle(newestPoint.x, newestPoint.y, 3.0f, GREEN);
        }
        DrawCircle(position.x, position.y, 3, DARKGREEN);
        const char *cur_vec_text = TextFormat("%i", currentVecWall);
        DrawText(cur_vec_text, 10, 40, 40, GREEN);

    }
    DrawText(currentType.c_str(), 800, 10, 30, YELLOW);
    
    
}