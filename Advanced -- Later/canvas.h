#include <raylib.h>
#include "iostream"

class Canvas{
    private:
        Vector2 TRUE_SIZE;
        Vector2 seen_size;
        int MARGIN = 0;
    public:
        Canvas(int margin, Vector2 size){
            MARGIN = margin;
            TRUE_SIZE = size;
        }

        void Draw(Vector2 position, Vector2 screensize, Vector2 max_prec){
            float proc;
            float XSize = (screensize.x*max_prec.x-position.x)/TRUE_SIZE.x;
            float YSize = (screensize.y*max_prec.y-position.y)/TRUE_SIZE.y;
            if (XSize < YSize){
                proc = XSize;
            } else {
                proc = YSize;
            }

            float procX = proc - MARGIN*2/TRUE_SIZE.x;
            float procY = proc - MARGIN*2/TRUE_SIZE.y;
            seen_size = {TRUE_SIZE.x*proc - MARGIN*2, TRUE_SIZE.y*proc - MARGIN*2};

            DrawRectangle(MARGIN+position.x, MARGIN+position.y, seen_size.x, seen_size.y, RAYWHITE);
            DrawRectangleLines(position.x, position.y, TRUE_SIZE.x*proc, TRUE_SIZE.y*proc, GRAY);                   // Draw rectangle outline
        }

        void DrawObject(){

        }
};