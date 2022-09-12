#include <raylib.h>
#include <iostream>
#include <math.h>

// #define PI 3.14159265

class Car{
    private:
        const Vector2 size = {30,18};
        Vector2 position;
        float angle;

        double speed = 0;
        const double accel = 1000.0;
        const double max_speed = 500.0;
        const double friction = 800.0;
        const double turnSpeed = 200.0;

        float speedTurn;

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
                speed+=accel*delta;
            }
            if(IsKeyDown(KEY_DOWN)){
                speed-=accel*delta;
            }

            if (speed>0.0){
                speed-=friction*delta;
            }
            if (speed<0.0){
                speed+=friction*delta;
            }
            

            if(speed>max_speed){
                speed = max_speed;
            } else if(speed<-max_speed/2){
                speed = -max_speed/2;
            }
            
            if(speed!=0){
                speedTurn = speed/float(max_speed);
                if(IsKeyDown(KEY_LEFT)){
                    angle-=turnSpeed*speedTurn*delta;
                }
                if(IsKeyDown(KEY_RIGHT)){
                    angle+=turnSpeed*speedTurn*delta;
                }
            }

            position.y-=sin(-angle*PI/180.0)*speed*delta;
            position.x-=cos(-angle*PI/180.0)*-speed*delta;
            
        }
};