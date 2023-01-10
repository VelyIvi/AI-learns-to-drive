class AiGrid{
private:
    int maxX, maxY;
    float* table;
public:
    AiGrid(int mX, int mY);
    ~AiGrid();
    float& at(int x, int y);
    void randomizeWeights();
};

AiGrid::~AiGrid() {
    delete table;
    table = nullptr;
}

AiGrid::AiGrid(int maxX, int maxY) {
    table = new float[maxX*maxY];
    this->maxX = maxX;
    this->maxY = maxY;
}

float& AiGrid::at(int x, int y){
    if(x < maxX && y < maxY){
        return table[int(y * maxX + x)];
    }
    throw std::invalid_argument("AiGrid::Invalid value::Value out of range");
}

void AiGrid::randomizeWeights() {
    for(int i = 0; i<maxX*maxY; i++){
        table[i] = get_random(-1, 1);
    }
}