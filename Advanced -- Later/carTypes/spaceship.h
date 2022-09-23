#include <raylib.h>
#include <iostream>
#include <math.h>

// #define PI 3.14159265

class Car{
    private:
        const Vector2 size = {30,18};
        Vector2 position;
        float angle;

        Vector2 speed;
        const float accel = 1200.0; //accelaration > friction
        const float max_speed = 500.0;
        const float friction = 800.0;
        const float turnSpeed = 300.0;

    public:
        Car(Vector2 pos){
            position = pos;
        }

        Rectangle getRec(){
            return Rectangle{position.x-size.x/2, position.y-size.y/2, size.x, size.y};
        }

        void Draw(){
            DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, angle, WHITE);
        }

        void Update(float delta){
            if (IsKeyDown(KEY_UP)){
                speed.y+=sin(angle*PI/180.0)*accel*delta;
                speed.x+=cos(angle*PI/180.0)*accel*delta;
            }
            if(IsKeyDown(KEY_DOWN)){
                speed.y-=sin(angle*PI/180.0)*accel*delta;
                speed.x-=cos(angle*PI/180.0)*accel*delta;
            }

            float speedNum = sqrt(speed.x*speed.x+speed.y*speed.y);

            // if (speed.y>0){
            //     speed.y-=sin(angle*PI/180.0)*friction*delta;
            // }else if (speed.y>0){
            //     speed.y-=sin(angle*PI/180.0)*friction*delta;
            // }
            // if (speed.x<0){
            //     speed.x+=cos(angle*PI/180.0)*friction*delta;
            // }else if (speed.x<0){
            //     speed.x+=cos(angle*PI/180.0)*friction*delta;
            // }

            // if(speedNum>max_speed){
            //     speed.y=sin(-angle*PI/180.0)*max_speed;
            //     speed.x=cos(-angle*PI/180.0)*max_speed;
            // } else if(speedNum<-max_speed){
            //     speed.y=sin(-angle*PI/180.0)*-max_speed;
            //     speed.x=cos(-angle*PI/180.0)*-max_speed;
            // }
            
            std::cout<<speed.x<<"  "<<speed.y<<"\n";


            if(IsKeyDown(KEY_LEFT)){
                angle-=turnSpeed*delta;
            }
            if(IsKeyDown(KEY_RIGHT)){
                angle+=turnSpeed*delta;
            }

            position.y+=speed.y*delta;
            position.x+=speed.x*delta;
            
            if (position.x>1500){
                position.x -= 1500;
            } else if (position.x<0){
                position.x += 1500;
            }
            if (position.y>800){
                position.y -= 800;
            } else if (position.y<0){
                position.y += 800;
            }
        }
};