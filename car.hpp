#include "sensor.hpp"
#include "network.hpp"


//Controls controls;

class Car{
public:
    const std::vector<int> nnLayerSizes = {9,6,4};
    NeuralNetwork nn;
    Sensor sensor;
private:
    const Vector2 size = {20,12};

    float speed = 0;
    const float accel = 400.0; //acceleration > friction
    const float max_speed = 500.0;
    const float friction = 350.0;
    const float turnSpeed = 110.0;

    void CheckCollisions();
public:
    Vector2 lastPos{};
    Vector2 position;
    float rotation;
    std::vector<std::vector<Vector2>>* wall;
    std::vector<std::vector<Vector2>>* check;


    bool alive = true;

    Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>> *c);
//    Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>>* w, std::vector<std::vector<Vector2>> *c, NeuralNetwork&& newNN);



    ~Car();
    void UpdateValues(Vector2& pos, float& rot, bool lives);
    void ResetValues(Vector2& pos, float& rot, bool lives);


    Rectangle getRec();
    void Draw();
    void Draw(Simulation * canvas);

    void DrawBest();
    void Update(float& delta);
    bool Collider(std::vector<std::vector<Vector2>>* array) const;
    std::vector<int> CheckCollider(std::vector<std::vector<Vector2>>* array) const;
    std::vector<int> checkCollided;
    int points = 0;
    int laps = 0;


    float currentSecCheckpoint = 0;
    const float maxSecNoCheckpoint = 2;

    void DrawBest(Simulation *canvas);
};

Car::Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>> *w, std::vector<std::vector<Vector2>> *c) : sensor(w), nn(this->nnLayerSizes){
    wall = w;
    check = c;
    position = pos;
    rotation = rot;

    sensor.Update(pos, rot);
}

//Car::Car(Vector2 pos, float rot, std::vector<std::vector<Vector2>> *w, std::vector<std::vector<Vector2>> *c, NeuralNetwork&& copyNN) : sensor(w), nn(std::move(copyNN)){
//    wall = w;
//    check = c;
//    position = pos;
//    rotation = rot;
//
//    sensor.Update(pos, rot);
//    std::cout<<"b\n";
//}

Car::~Car() {
//    std::cout<<"Called car destructor\n";
}

void Car::UpdateValues(Vector2& pos, float& rot, bool lives){
    position = pos;
    rotation = rot;
    alive = lives;
}

Rectangle Car::getRec() {
    return Rectangle{position.x, position.y, size.x, size.y};
}


void Car::DrawBest(){
    if(alive){
        sensor.Draw(position);
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarBestColor);
    } else {
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarBestDeadColor);
    }
    DrawCircleV(position, 3, RED);

}

void Car::DrawBest(Simulation* canvas){
    if(alive){
//        sensor.Draw(position);
        sensor.Draw(position, canvas);
        canvas->DrawRectangleProSim(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarBestColor);
    } else {
        canvas->DrawRectangleProSim(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarBestDeadColor);
    }
    canvas->DrawCircleVSim(position, 3, RED);

}

void Car::Draw(){
    if(alive){
//        sensor.Draw(position);
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarColor);
    } else {
        DrawRectanglePro(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarDeadColor);
    }
}

void Car::Draw(Simulation* canvas){
    if(alive){
        canvas->DrawRectangleProSim(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarColor);
    } else {
        canvas->DrawRectangleProSim(getRec(), Vector2{size.x/2, size.y/2}, rotation, CarDeadColor);
    }
}



void Car::Update(float& delta){

    if(!alive){
        return;
    }

    lastPos = position;

    std::vector<float> AiInputs (nnLayerSizes.at(0));
    for(int i= 0; i<sensor.rayCount; i++){
        AiInputs.at(i) = (sensor.readings.at(i).z/sensor.rayLength*2-1); ////range -1 <-> 1
    }
//    AiInputs.at(9) = speed/max_speed;

    std::vector<float> AiOutputs = nn.getOutput(AiInputs);

    if(AiOutputs.at(0) == 1){
        rotation-= turnSpeed * delta;
    }
    if(AiOutputs.at(1) == 1){
        rotation+= turnSpeed * delta;
    }
    if(AiOutputs.at(2) == 1){
        speed+=accel*delta;
    }
    if(AiOutputs.at(3) == 1){
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
    } else if(speed<-max_speed/7){
        speed = -max_speed/7;
    }

    position.y-=float(sin(-(rotation) * PI / 180.0) * speed * delta);
    position.x-=float(cos(-(rotation) * PI / 180.0) * -speed * delta);

    sensor.Update(position, rotation);
    CheckCollisions();

    if(currentSecCheckpoint > maxSecNoCheckpoint){
        alive = false;
    }
    currentSecCheckpoint=currentSecCheckpoint+delta;
}

bool Car::Collider(std::vector<std::vector<Vector2>>* array) const{
    Vector2 lastArrayPoint = {-1,-1};
    for(std::vector<Vector2>& currentArray : *array){
        for(Vector2 & currentArrayPoint : currentArray){
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

std::vector<int> Car::CheckCollider(std::vector<std::vector<Vector2>>* array) const{
    Vector2 lastArrayPoint = {-1,-1};
    std::vector<int> collision = {};
    for(int x = 0; x<array->size(); x++){
        for(Vector2 & currentArrayPoint : array->at(x)){
            if(lastArrayPoint.x >= 0 && lastArrayPoint.y >= 0){
                if (simpleIntersect(lastPos, position, lastArrayPoint, currentArrayPoint)){
                    collision.push_back(x);
                }
            }
            lastArrayPoint = currentArrayPoint;
        }
        lastArrayPoint = {-1,-1};
    }
    return collision;
}

void Car::CheckCollisions(){
    if (Collider(wall)){
        alive = false;
    }
    std::vector<int> CheckCollidedNum;
    CheckCollidedNum = CheckCollider(check);
    for(int & CheckCollidedCurrent: CheckCollidedNum) {
        if (0 <= CheckCollidedCurrent) {
            std::sort(checkCollided.begin(), checkCollided.end());
            if (!std::binary_search(checkCollided.begin(), checkCollided.end(), CheckCollidedCurrent)) {
                points++;
                currentSecCheckpoint = 0;
                checkCollided.push_back(CheckCollidedCurrent);
            }
        }
    }

    if(checkCollided.size() == check->size()){
        checkCollided.clear();
        laps++;
    }
}

void Car::ResetValues(Vector2& pos, float& rot, bool lives) {
    UpdateValues(pos, rot, lives);
    checkCollided.clear();
    points = 0;
    laps = 0;
    speed = 0;


    currentSecCheckpoint = 0;
}
