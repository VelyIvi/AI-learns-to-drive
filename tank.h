#include "controls.hpp"
#include "sensor.h"
#include "network.h"


Controls controls;
Level levl(4,10);

class Car{
    Sensor sensor;

private:
    const Vector2 size = {20,12};

    float speed = 0;
    const float accel = 500.0; //acceleration > friction
    const float max_speed = 600.0;
    const float friction = 300.0;
    const float turnSpeed = 100.0;

    void CheckCollisions();
public:
    Vector2 lastPos{};
    Vector2* position;
    float* angle;
    std::vector<std::vector<Vector2>>* wall;



    bool alive = true;

    Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>>* w);



    ~Car();

    Rectangle getRec();
    void Draw();
    void Update(float delta);
};

Car::Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>> *w) : wall(w), position(new Vector2(pos)), angle(new float(rot)), sensor(wall, angle, position){
}

Car::~Car() {
    std::cout<<"Called car destructor\n";
    delete position;
    delete angle;
    position = nullptr;
    angle = nullptr;
}

Rectangle Car::getRec() {
    return Rectangle{position->x, position->y, size.x, size.y};
}

void Car::Draw(){
    if(alive){
        sensor.Draw();
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, *angle, CarColor);
    } else {
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, *angle, CarDeadColor);
    }
}

void Car::Update(float delta){

    if(!alive){
//        *position = lastPos;
        return;
    }


    lastPos = *position;

    controls.Update();

    if(controls.left){
        *angle-=turnSpeed*delta;
    }
    if(controls.right){
        *angle+=turnSpeed*delta;
    }
    if (controls.forward){
        speed+=accel*delta;
    }
    if(controls.reverse){
        speed-=accel*delta;
    }

    if (speed>0.0){
        speed-=friction*delta;
        if(speed < 0.0){
            speed = 0;
        }
    }
    if (speed<0.0){
        speed+=friction*delta;
        if(speed > 0.0){
            speed = 0;
        }
    }
    
    if(speed>max_speed){
        speed = max_speed;
    } else if(speed<-max_speed/3){
        speed = -max_speed/3;
    }

    position->y-=sin(-(*angle)*PI/180.0)*speed*delta;
    position->x-=cos(-(*angle)*PI/180.0)*-speed*delta;

    sensor.Update();
    CheckCollisions();

}


void Car::CheckCollisions(){
    for(auto & i : *wall){
        for(int i2 = 0; i2<i.size()-1; i2++){
            if (getIntersection(lastPos, *position, i.at(i2), i.at(i2+1), sqrt(pow(lastPos.x-position->x,2) + pow(lastPos.y-position->y, 2))).w == 1){
                alive = false;
            }
        }
    }
}





