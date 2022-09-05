#include <raylib.h>

class Canvas{
    private:
        Vector2 TRUE_SIZE = {1500, 800};
        Vector2 seen_size;
        int MARGIN = 20;
    public:
        Canvas(){

        }

        void XReduction(int x){
            float proc = (x-MARGIN*1)/TRUE_SIZE.x;
            seen_size = {TRUE_SIZE.x*proc, TRUE_SIZE.y*proc};
        }


        void Draw(){
            DrawRectangle(MARGIN, MARGIN, seen_size.x, seen_size.y, RED);
        }

        void Update(){

        }
};