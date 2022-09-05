#include <raylib.h>
#include "iostream"

class Canvas{
    private:
        Vector2 TRUE_SIZE = {1500, 800};
        Vector2 seen_size;
        int MARGIN = 10;
    public:
        Canvas(){

        }

        void XReduction(int x){
            float procX = x/TRUE_SIZE.x - MARGIN*2/TRUE_SIZE.x;
            float procY = x/TRUE_SIZE.x - MARGIN*2/TRUE_SIZE.y;
            seen_size = {TRUE_SIZE.x*procX, TRUE_SIZE.y*procY};
        }


        void Draw(){
            DrawRectangle(MARGIN, MARGIN, seen_size.x, seen_size.y, RED);
        }

        void Update(){

        }
};