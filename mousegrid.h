#define DARKYELLOW  (Color){177, 174, 0, 255}

class MouseGrid {
    private:
        Vector2 real_position;
        Vector2 position;
        Vector2 newestPoint;
    public:
        bool* edit;
        Map* m;
        int currentVec = 0;

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
    if(IsKeyPressed(KEY_L)){
        currentVec++;
    }
    if(IsKeyPressed(KEY_J)){
        currentVec--;
    }
    
    if(currentVec<0){
            currentVec = m->map_points.size()-1;
    }
    if(currentVec>m->map_points.size()-1){
        currentVec = 0;
    }


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

    if (IsKeyPressed(KEY_K)){
        if (m->map_points.size()>0){
            for(int h = 0 ; h<=m->map_points.size()-1; h++){
                if (m->map_points.at(h).size()==0){
                    currentVec = h;
                    return;
                }
            }
        }

        m->map_points.push_back({});
        if (m->map_points.size()>1){
            currentVec = m->map_points.size()-1;
        }
    }

    position = {round(real_position.x/gridSize)*gridSize, round(real_position.y/gridSize)*gridSize};
    if(m->map_points.size() < 1){
        return;
    }

    if (m->map_points.at(currentVec).size() < 1){
        if(IsMouseButtonPressed(0)){
            m->map_points.at(currentVec).push_back(position);
            int vecSize = m->map_points.at(currentVec).size()-1;
            newestPoint = m->map_points.at(currentVec).at(vecSize);
        }
        else if(IsMouseButtonPressed(1)){
            m->map_points.erase(m->map_points.begin() + currentVec);
            if(currentVec<0){
                currentVec = m->map_points.size()-1+0;
            }
            if(currentVec>m->map_points.size()-1){
                currentVec = 0;
            }
        }
       return;
    }
    int vecSize = m->map_points.at(currentVec).size()-1;
    newestPoint = m->map_points.at(currentVec).at(vecSize);

    if(IsMouseButtonPressed(0)){
        if (position.x != newestPoint.x || position.y != newestPoint.y){
            m->map_points.at(currentVec).push_back(position);
        }
    } else if(IsMouseButtonPressed(1)){        
        m->map_points.at(currentVec).pop_back(); 
    }
}

void MouseGrid::Draw(){
    if (*edit==false){
        DrawCircle(real_position.x, real_position.y, 2, RED);
        return;
    }
    DrawCircle(real_position.x, real_position.y, 3, DARKYELLOW);
    if (m->map_points.size()<=0){
        return;
    }
    if(m->map_points.at(currentVec).size() > 0){
        DrawLineV(newestPoint, position, DARKGREEN);
        DrawCircle(newestPoint.x, newestPoint.y, 3.0f, GREEN);
    }
    DrawCircle(position.x, position.y, 3, DARKGREEN);
    const char *cur_vec_text = TextFormat("%i", currentVec);
    DrawText(cur_vec_text, 100, 10, 50, YELLOW);
}