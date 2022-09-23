#include "controls.h"

#define PI 3.14159265


class Car{
    private:
        const Vector2 size = {30,18};
        Vector2 position;
        float angle;

        float speed = 0;
        const float accel = 1200.0; //accelaration > friction
        const float max_speed = 500.0;
        const float friction = 550.0;
        const float turnSpeed = 300.0;

    public:
        Car(Vector2 pos){
            position = pos;
        }
        Rectangle getRec(){
            return Rectangle{position.x, position.y, size.x, size.y};
        }

        void Draw(){
            DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, angle, WHITE);
        }

        void Update(float delta);
};

Controls controls;


void Car::Update(float delta){
    controls.Update();

    if(controls.left == true){
        angle-=turnSpeed*delta;
    }
    if(controls.right == true){
        angle+=turnSpeed*delta;
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

    position.y-=sin(-angle*PI/180.0)*speed*delta;
    position.x-=cos(-angle*PI/180.0)*-speed*delta;
    
    // if (position.x>1500){
    //     position.x -= 1500;
    // } else if (position.x<0){
    //     position.x += 1500;
    // }
    // if (position.y>800){
    //     position.y -= 800;
    // } else if (position.y<0){
    //     position.y += 800;
    // }
}