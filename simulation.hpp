#include <raylib.h>
//#include "network.hpp"

class Simulation {
protected:
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

    void DrawTextSim(const char *text, int posX, int posY, int fontSize, Color color);

    bool GuiButtonSim(Rectangle rectangle, const char *string);

    void DrawNN(NeuralNetwork & network);
};




void Simulation::Draw(Vector2 pos, Vector2 screensize, Vector2 max_prec) {
    position = pos;
    float XSize = (screensize.x*max_prec.x)/SimulationSize.x;
    float YSize = (screensize.y*max_prec.y)/SimulationSize.y;
    if (XSize < YSize){
        proc = XSize;
    } else {
        proc = YSize;
    }

;
    CurrentSize = {SimulationSize.x*proc - margin*2, SimulationSize.y*proc - margin*2};
    DrawRectangle(position.x, position.y, screensize.x*max_prec.x, screensize.y*max_prec.y, BLACK);
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

void Simulation::DrawTextSim(const char *text, int posX, int posY, int fontSize, Color color){
    DrawText(text, margin+position.x+posX*proc, margin+position.y+posY*proc, fontSize*proc, color);
}

//bool Simulation::GuiButtonSim(Rectangle rectangle, const char * string) {
//    std::cout<<"e\n";
//    return GuiButtonSim((Rectangle){ margin+position.x+rectangle.x*proc,margin+position.y+rectangle.y*proc, rectangle.width*proc, rectangle.height*proc }, string);
//}

//
std::vector<char *> outputEmotes = {"LEFT","RIGHT","FORWARD","REVERSE"};
void Simulation::DrawNN(NeuralNetwork & network){
    const int mar = 100;
    int layerSize = network.layers.size();
    float yDisplacement = (SimulationSize.y-mar)/(layerSize);

    for(int y = 0; y<layerSize; y++){
        Layer & layer = network.layers.at(y);
        float xDisplacement = (SimulationSize.x-mar)/(layer.input.size()-1);
        for(int x = 0; x<layer.input.size(); x++){
            DrawCircleVSim(Vector2{x*xDisplacement +mar/2, SimulationSize.y -(y * yDisplacement +mar/2)}, 20,
                           ColorMixLin(BLACK, YELLOW, (layer.input.at(x)+1)/2));
        }
    }
    for(int l = 0; l<network.layers.at(layerSize-1).output.size(); l++){
        Layer & layer = network.layers.at(layerSize-1);
        float xDisplacement = (SimulationSize.x-mar)/(layer.output.size()-1);
        DrawCircleVSim(Vector2{l*xDisplacement +mar/2, SimulationSize.y -(layerSize * yDisplacement +mar/2)}, 20, ColorMixLin(BLACK, YELLOW, (layer.output.at(l))));
        if(l < network.layers.at(layerSize-1).output.size()){
            DrawTextSim(outputEmotes.at(l), l*xDisplacement +mar/2, SimulationSize.y -(layerSize * yDisplacement +mar/2)-40,10,WHITE);
        }
    }
}