#include "controls.h"
#include "sensor.h"
#include "network.h"


Controls controls;


//Level lvel(4,10);


Sensor sensor;


class Car{
    private:
        const Vector2 size = {20,12};

        float speed = 0;
        const float accel = 500.0; //accelaration > friction
        const float max_speed = 600.0;
        const float friction = 300.0;
        const float turnSpeed = 100.0;

        void CheckCollisions();
    public:
        Vector2 lastPos;
        Vector2* position = new Vector2;
        float* angle = new float;

        std::vector<std::vector<Vector2>>* wall;

        bool alive = true;

        Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>>* w){
            position->x = pos.x;
            position->y = pos.y;

            *angle = rot;
            wall = w;

            sensor.wall = w;
            sensor.position = position;
            sensor.angle = angle;
        }

        ~Car(){
            std::cout<<"Called car destructor\n";
            delete position;
            delete angle;
            position = NULL;
            angle = NULL;
        }

        Rectangle getRec(){
            return Rectangle{position->x, position->y, size.x, size.y};
        }
        void Draw();
        void Update(float delta);
};

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

    if(controls.left == true){
        *angle-=turnSpeed*delta;
    }
    if(controls.right == true){
        *angle+=turnSpeed*delta;
    }
    if (controls.forward == true){
        speed+=accel*delta;
    }
    if(controls.reverse == true){
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
    for(int i = 0; i<wall->size(); i++){
        for(int i2 = 0; i2<wall->at(i).size()-1; i2++){
            if (getIntersection(lastPos, *position, wall->at(i).at(i2), wall->at(i).at(i2+1), sqrt(pow(lastPos.x-position->x,2) + pow(lastPos.y-position->y, 2))).w == 1){
                alive = false;
            }
        }
    }
}