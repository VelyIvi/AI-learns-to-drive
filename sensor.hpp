#include "utils.hpp"
//#include "simulation.hpp"

class Sensor {
private:
    const float raySpread = 180+60; //in degrees

    std::vector<Vector4> rays;
    void GetReading();
    void CastRays(Vector2& position, float& angle);

public:
    const int rayCount = 9;
    const int rayLength = 200;

    std::vector<std::vector<Vector2>>* wall;
    std::vector<Vector4> readings;

    Sensor(std::vector<std::vector<Vector2>>* w);
    ~Sensor();

    void Update(Vector2& position, float& angle);
    void Draw(Vector2& position);
    void Draw(Vector2& position, Simulation *canvas);


};



Sensor::Sensor(std::vector<std::vector<Vector2>>* w){
    wall = w;
}

Sensor ::~Sensor (){
//    std::cout<<"Called Sensor destructor"<<"\n";
}

void Sensor ::Update(Vector2& position, float& angle){
    CastRays(position, angle);
}


void Sensor ::CastRays(Vector2& position, float& angle){
    rays.clear();
    for(int i=0; i<rayCount; i++){
        Vector2 startPos = position;
        float ang = lerp(-0.5f*raySpread+(angle), 0.5f*raySpread+(angle), float(i)/(rayCount-1));
        Vector2 endPos = {float(cos(-(ang)*PI/180.0)*rayLength+position.x), float(sin(-(ang)*PI/180.0)*-rayLength+position.y)};
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
            if(hit.at(f).z <= currentClosest.z && hit.at(f).w == 1){
                currentClosest = hit.at(f);
            }
        }
        readings.push_back(currentClosest);
    }
}

void Sensor::Draw(Vector2& position){
    int i = 0;
    for(Vector4 readingsVector : readings){
        if(readingsVector.w == 1){
            DrawLineV({readingsVector.x, readingsVector.y}, {rays.at(i).z, rays.at(i).w}, RaycastShadeColor);

            DrawLineV(position, {readingsVector.x, readingsVector.y}, RaycastColor);
            DrawCircle(readingsVector.x, readingsVector.y, 3, RaycastColor);
        } else {
            DrawLineV(position, {rays.at(i).z, rays.at(i).w}, RaycastColor);
        }
        i++;
    }
}

void Sensor::Draw(Vector2 &position, Simulation *canvas) {
    int i = 0;
    for(Vector4 readingsVector : readings){
        if(readingsVector.w == 1){
            canvas->DrawLineVSim({readingsVector.x, readingsVector.y}, {rays.at(i).z, rays.at(i).w}, RaycastShadeColor);

            canvas->DrawLineVSim(position, {readingsVector.x, readingsVector.y}, RaycastColor);
            canvas->DrawCircleVSim({readingsVector.x, readingsVector.y}, 3, RaycastColor);
        } else {
            canvas->DrawLineVSim(position, {rays.at(i).z, rays.at(i).w}, RaycastColor);
        }
        i++;
    }
}
