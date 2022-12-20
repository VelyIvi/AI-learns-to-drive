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

AiGrid::AiGrid(int mX, int mY) {
    table = new float[mX*mY];
    maxX = mX;
    maxY = mY;
}

float& AiGrid::at(int x, int y){
    if(x > maxX-1){
        throw std::invalid_argument("AiGrid::Invalid value for X");
    }
    if(y > maxY-1){
        throw std::invalid_argument("AiGrid::Invalid value for Y");
    }
    return table[int(y * maxX + x)];
}

void AiGrid::randomizeWeights() {
    for(int i = 0; i<maxX*maxY; i++){
        table[i] = get_random(-1, 1);
    }
}

class Level{
    AiGrid grid;
private:
    float *input;
    float *output;
    float *bias;

    float *weights;
public:
    Level(int inputCount, int outputCount);
    ~Level();
};

Level::Level(int inputCount, int outputCount) : grid(inputCount, outputCount){
    input = new float[inputCount];
    output = new float[outputCount];
    bias = new float[outputCount];


    weights = new float[inputCount*outputCount];
    grid.randomizeWeights();

    grid.at(1, 1) = 0;
    std::cout<<grid.at(1,1)<<"\n";
}

Level::~Level(){
    delete[] input;
    delete[] output;
    delete[] bias;
    delete[] weights;

    input = nullptr;
    output = nullptr;
    bias = nullptr;
    weights = nullptr;

    std::cout<<"Called Neural Network Level destructor\n";
}