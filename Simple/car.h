#include <raylib.h>

class Car{
    private:
        Vector2 size = {30,18};
        Vector2 position = {10,10};
    public:
        Car(){
            
        }

        ~Car(){

        }

        Rectangle getRec(){
            return Rectangle{position.x-size.x/2, position.y-size.y/2, size.x, size.y};
        }

        void Draw(){
            DrawRectanglePro(getRec(), position, 80.0f ,WHITE);
        }
};