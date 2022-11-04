#include "utils.h"

class Sensor {
    private:
        const int rayLength = 200;
        const float rayCount = 7;
        const float raySpread = 180+90+90/2; //in degrees

        std::vector<Vector4> rays;
        void GetReading();
        void CastRays();

        std::vector<Vector3> readings;
    public:
        float* angle;
        Vector2* position;
        std::vector<std::vector<Vector2>>* wall;


        Sensor ();
        ~Sensor ();

        void Update();
        void Draw();

};

Sensor ::Sensor (){

}

Sensor ::~Sensor (){
    std::cout<<"Called Sensor destructor"<<"\n";
    angle = NULL;
    position = NULL;
}

void Sensor ::Update(){
    CastRays();
}


void Sensor ::CastRays(){
    rays.clear();
    for(int i=0; i<rayCount; i++){
        Vector2 startPos = {position->x, position->y};
        float ang = lerp(-0.5*raySpread+(*angle), 0.5*raySpread+(*angle), i/(rayCount-1));
        Vector2 endPos = {cos(-(ang)*PI/180.0)*rayLength+position->x, sin(-(ang)*PI/180.0)*-rayLength+position->y};
        rays.push_back({startPos.x, startPos.y, endPos.x, endPos.y});
    }
}

void Sensor ::GetReading(){

}

void Sensor ::Draw(){
    for (int x = 0; x < rayCount; x++){
        std::vector<Vector3> hit;
        for(int e = 0; e<wall->size(); e++){
            for(int e2 = 0; e2<wall->at(e).size()-1; e2++){
                Vector3 p = getIntersection({rays.at(x).x, rays.at(x).y}, {rays.at(x).z, rays.at(x).w}, wall->at(e).at(e2), wall->at(e).at(e2+1), rayLength);
                hit.push_back(p);
            }
        }
        Vector3 currentClosest;
        for(int f = 0; f < hit.size(); f++){
            if(hit.at(f).z < currentClosest.z){
                currentClosest = hit.at(f);
            }
        }
        std::cout<<currentClosest.z<<"\n";

        DrawCircle(currentClosest.x, currentClosest.y, 5, RED);
    }
    
}