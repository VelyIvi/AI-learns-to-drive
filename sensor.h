#include "utils.h"

class Sensor{
    private:
        int rayLength = 200;
        float rayCount = 7;
        float raySpread = 180+60; //in degrees

        std::vector<Vector4> rays;
        void GetReading();
        void CastRays();

        std::vector<Vector3> readings;
    public:
        float* angle;
        Vector2* position;

        Sensor();
        ~Sensor();

        void Update();
        void Draw();

};
Sensor::~Sensor(){
    
}
Sensor::Sensor(){

}

void Sensor::Update(){
    CastRays();
}


void Sensor::CastRays(){
    rays.clear();
    for(int i=0; i<rayCount; i++){
        Vector2 startPos = {position->x, position->y};
        float ang = lerp(-0.5*raySpread+(*angle), 0.5*raySpread+(*angle), i/(rayCount-1));
        Vector2 endPos = {cos(-(ang)*PI/180.0)*rayLength+position->x, sin(-(ang)*PI/180.0)*-rayLength+position->y};
        // std::cout<<startPos.x<<"  "<< startPos.y<<"  "<< endPos.x<<"  "<< endPos.y<<"\n";
        rays.push_back({startPos.x, startPos.y, endPos.x, endPos.y});
    }
}

void Sensor::GetReading(){

}

void Sensor::Draw(){
    for (int x = 0; x < rayCount; x++){
        DrawLineEx({rays.at(x).x, rays.at(x).y}, {rays.at(x).z, rays.at(x).w}, 1, RaycastColor);
    }
}