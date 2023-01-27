class Grid{
private:
public:
    int maxX, maxY;
    std::vector<float> table;
    Grid(int maxX, int maxY);
    ~Grid();
    float& at(int x, int y);
    void randomizeWeights();
};

Grid::~Grid() = default;

Grid::Grid(int maxX, int maxY) {
    table = std::vector<float>(maxX*maxY);
    this->maxX = maxX;
    this->maxY = maxY;
}

float& Grid::at(int x, int y){
    return table.at(y * maxX + x);
}

void Grid::randomizeWeights() {
    for(float & currentValue : table){
        currentValue = get_random(-1, 1);
    }
}