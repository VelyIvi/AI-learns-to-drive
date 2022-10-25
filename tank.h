#include "controls.h"
#include "sensor.h"


#define PI 3.14159265

Controls controls;

Sensor sensor;


class Car{
    private:
        const Vector2 size = {30,18};
        Vector2* position = new Vector2;
        float* angle = new float;

        float speed = 0;
        const float accel = 500.0; //accelaration > friction
        const float max_speed = 300.0;
        const float friction = 200.0;
        const float turnSpeed = 150.0;

    public:
        Car(Vector2 pos, float rot){
            std::cout<<pos.x<<" "<<pos.y<<"\n";
            position->x = pos.x;
            position->y = pos.y;

            *angle = rot;


            sensor.position = position;
            sensor.angle = angle;
        }

        ~Car(){
            // std::cout<<&position<<"  "<<position->x<<"  "<<&sensor.position<<"\n";
            sensor.~Sensor();
            // delete position;
            // delete angle;
            // position = NULL;
            // angle = NULL;
        }

        Rectangle getRec(){
            return Rectangle{position->x, position->y, size.x, size.y};
        }
        void Draw();
        void Update(float delta);
};

void Car::Draw(){

    DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, *angle, CarColor);
    sensor.Draw();
}

void Car::Update(float delta){
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
    } else if(speed<-max_speed/2){
        speed = -max_speed/2;
    }

    position->y-=sin(-(*angle)*PI/180.0)*speed*delta;
    position->x-=cos(-(*angle)*PI/180.0)*-speed*delta;

    sensor.Update();
}