#include "utils.hpp"

class Sensor {
    private:
        const int rayLength = 250;
        const float rayCount = 9;
        const float raySpread = 180+60; //in degrees

        std::vector<Vector4> rays;
        void GetReading();
        void CastRays();

    public:
        float* angle;
        Vector2* position;
        std::vector<std::vector<Vector2>>* wall;
        std::vector<Vector4> readings;


        Sensor ();
        ~Sensor ();

        void Update();
        void Draw();

};

Sensor ::Sensor (){
    
}

Sensor ::~Sensor (){
    std::cout<<"Called Sensor destructor"<<"\n";
    angle = nullptr;
    position = nullptr;
}

void Sensor ::Update(){
    CastRays();
}


void Sensor ::CastRays(){
    rays.clear();
    for(int i=0; i<rayCount; i++){
        Vector2 startPos = {position->x, position->y};
        float ang = lerp(-0.5f*raySpread+(*angle), 0.5f*raySpread+(*angle), float(i)/(rayCount-1));
        Vector2 endPos = {float(cos(-(ang)*PI/180.0)*rayLength+position->x), float(sin(-(ang)*PI/180.0)*-rayLength+position->y)};
        rays.push_back({startPos.x, startPos.y, endPos.x, endPos.y});
    }
    GetReading();
}

void Sensor ::GetReading(){
    readings.clear();
    for (int x = 0; x < rayCount; x++){
        std::vector<Vector4> hit;
        for(std::vector<Vector2> wallArray : *wall){
            for(int e2 = 0; e2<wallArray.size()-1; e2++){
                Vector4 p = getIntersection({rays.at(x).x, rays.at(x).y}, {rays.at(x).z, rays.at(x).w}, wallArray.at(e2), wallArray.at(e2+1), rayLength);
                hit.push_back(p);
            }
        }
        Vector4 currentClosest = {rays.at(x).z, rays.at(x).w,float(rayLength),0}; //inputs max to fix a bug
        for(int f = 0; f < hit.size(); f++){
            if(hit.at(f).z <= currentClosest.z){
                currentClosest = hit.at(f);
            }
        }
        readings.push_back(currentClosest);
    }
}

void Sensor::Draw(){
    int i = 0;
    for(Vector4 readingsVector : readings){
        if(readingsVector.w == 1){
            DrawLineV({readingsVector.x, readingsVector.y}, {rays.at(i).z, rays.at(i).w}, RaycastShadeColor);

            DrawLineV(*position, {readingsVector.x, readingsVector.y}, RaycastColor);
            DrawCircle(readingsVector.x, readingsVector.y, 3, RaycastColor);
        } else {
            DrawLineV(*position, {rays.at(i).z, rays.at(i).w}, RaycastColor);
        }
        i++;
    }
}