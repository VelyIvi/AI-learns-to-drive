#include <raylib.h>

class Simulation {
private:
    Vector2 SimulationSize;
public:
    Vector2 CurrentSize;
    Vector2 position;
    float margin = 0;
    float proc = 0;

    Simulation(Vector2 ss){
        SimulationSize = ss;
    }
    Color backgroundColor = BackGroundColor;
    void DrawRectangleProSim(Rectangle rec, Vector2 origin, float rotation, Color color);
//
    void Draw(Vector2 pos, Vector2 screensize, Vector2 max_prec);

    void DrawCircleVSim(Vector2 pos, float radius, Color color);

    void DrawLineVSim(Vector2 startPos, Vector2 endPos, Color color);
};




void Simulation::Draw(Vector2 pos, Vector2 screensize, Vector2 max_prec) {
    position = pos;
    float XSize = (screensize.x*max_prec.x-position.x)/SimulationSize.x;
    float YSize = (screensize.y*max_prec.y-position.y)/SimulationSize.y;
    if (XSize < YSize){
        proc = XSize;
    } else {
        proc = YSize;
    }

;
    CurrentSize = {SimulationSize.x*proc - margin*2, SimulationSize.y*proc - margin*2};

    DrawRectangle(margin+position.x, margin+position.y, CurrentSize.x, CurrentSize.y, backgroundColor);
    DrawRectangleLines(position.x, position.y, SimulationSize.x*proc, SimulationSize.y*proc, WHITE);                   // Draw rectangle outline
}

void Simulation::DrawRectangleProSim(Rectangle rec, Vector2 origin, float rotation, Color color) {
    Rectangle r {margin+position.x+rec.x*proc, margin+position.y+rec.y*proc, rec.width*proc, rec.height*proc};
    DrawRectanglePro(r ,Vector2{r.width/2, r.height/2}, rotation, color);
}
void Simulation::DrawCircleVSim(Vector2 pos, float radius, Color color) {
    DrawCircleV(Vector2{margin+position.x+pos.x*proc, margin+position.y+pos.y*proc}, radius*proc, color);
}

void Simulation::DrawLineVSim(Vector2 startPos, Vector2 endPos, Color color) {
    DrawLineV(Vector2 {margin+position.x+startPos.x*proc, margin+position.y+startPos.y*proc},Vector2 {margin+position.x+endPos.x*proc, margin+position.y+endPos.y*proc}, color);
}