class AiGrid{
private:
public:
    int maxX, maxY;
    std::vector<float> table;
    AiGrid(int maxX, int maxY);
    ~AiGrid();
    float& at(int x, int y);
    void randomizeWeights();
};

AiGrid::~AiGrid() = default;

AiGrid::AiGrid(int maxX, int maxY) {
    table = std::vector<float>(maxX*maxY);
    this->maxX = maxX;
    this->maxY = maxY;
}

float& AiGrid::at(int x, int y){
    return table.at(y * maxX + x);
}

void AiGrid::randomizeWeights() {
    for(float & currentValue : table){
        currentValue = get_random(-1, 1);
    }
}