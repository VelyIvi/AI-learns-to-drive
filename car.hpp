#include "controls.hpp"
#include "sensor.hpp"
#include "network.hpp"


Controls controls;

class Car{
    Level level;
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
    Vector2 position;
    float rotation;
    std::vector<std::vector<Vector2>>* wall;
    std::vector<std::vector<Vector2>>* check;


    bool alive = true;

    Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>> *c);
    ~Car();
    void UpdateValues(Vector2 pos, float rot, bool lives);

    Rectangle getRec();
    void Draw();
    void Update(float& delta);
    bool Collider(std::vector<std::vector<Vector2>>* array) const;
    int CheckCollider(std::vector<std::vector<Vector2>>* array) const;
    std::vector<int> checkCollided;
    int laps = 0;


    int currentFramesNotCheck = 0;
    const int maxFramesNotCheck = 180;
};

Car::Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>> *w, std::vector<std::vector<Vector2>> *c) : sensor(w), level(9,4){
    wall = w;
    check = c;
    position = pos;
    rotation = rot;

    sensor.Update(pos, rot);
}

Car::~Car() {
    std::cout<<"Called car destructor\n";
}

void Car::UpdateValues(Vector2 pos, float rot, bool lives){
    position = pos;
    rotation = rot;
    alive = lives;
}

Rectangle Car::getRec() {
    return Rectangle{position.x, position.y, size.x, size.y};
}

void Car::Draw(){
    if(alive){
        sensor.Draw(position);
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarColor);
    } else {
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarDeadColor);
    }
}

void Car::Update(float& delta){

    if(!alive){
        return;
    }


    lastPos = position;


    float AiInputs[sensor.rayCount];
    for(int i= 0; i<sensor.rayCount; i++){
        AiInputs[i] = (sensor.readings.at(i).z/sensor.rayLength);
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
    } else if(speed<-max_speed/5){
        speed = -max_speed/5;
    }

    position.y-=float(sin(-(rotation) * PI / 180.0) * speed * delta);
    position.x-=float(cos(-(rotation) * PI / 180.0) * -speed * delta);

    sensor.Update(position, rotation);
    CheckCollisions();

}
bool Car::Collider(std::vector<std::vector<Vector2>>* array) const{
    Vector2 lastArrayPoint = {-1,-1};
    for(const std::vector<Vector2>& currentArray : *array){
        for(Vector2 currentArrayPoint : currentArray){
            if(lastArrayPoint.x >= 0 && lastArrayPoint.y >= 0){
                if (simpleIntersect(lastPos, position, lastArrayPoint, currentArrayPoint)){
                    return true;
                }
            }
            lastArrayPoint = currentArrayPoint;
        }
        lastArrayPoint = {-1,-1};
    }
    return false;
}

int Car::CheckCollider(std::vector<std::vector<Vector2>>* array) const{
    Vector2 lastArrayPoint = {-1,-1};
    for(int x = 0; x<array->size(); x++){
        for(Vector2 currentArrayPoint : array->at(x)){
            if(lastArrayPoint.x >= 0 && lastArrayPoint.y >= 0){
                if (simpleIntersect(lastPos, position, lastArrayPoint, currentArrayPoint)){
                    return x;
                }
            }
            lastArrayPoint = currentArrayPoint;
        }
        lastArrayPoint = {-1,-1};
    }
    return -1;
}

void Car::CheckCollisions(){
    if (Collider(wall)){
        alive = false;
    }
    int CheckCollidedNum;
    CheckCollidedNum = CheckCollider(check);
    if (0<=CheckCollidedNum){
        std::sort(checkCollided.begin(), checkCollided.end());
        if(!std::binary_search(checkCollided.begin(), checkCollided.end(), CheckCollidedNum)){
//            std::cout<<CheckCollidedNum<<"\n";
            currentFramesNotCheck = 0;
            checkCollided.push_back(CheckCollidedNum);
        }
    }

    if(checkCollided.size() == check->size()){
        checkCollided.clear();
        laps++;
    }

    if(currentFramesNotCheck > maxFramesNotCheck){
        alive = false;
    }
    currentFramesNotCheck++;
}
