class AiGrid{
private:
    float maxX, maxY;
    float *table;
public:
    AiGrid(int mX, int mY);
    float Look(int x, int y);
};
AiGrid::AiGrid(int mX, int mY) {
    table = new float[mX, mY];
    maxX = mX;
    maxY = mY;
}

float AiGrid::Look(int x, int y) {
//    return table[y * maxX + x];
    return 0;
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
    void randomizeWeights();
};

Level::Level(int inputCount, int outputCount) : grid(inputCount, outputCount){
    input = new float[inputCount];
    output = new float[outputCount];
    bias = new float[outputCount];


    //!-! can't use a dynamic 2d array so i'll create my own class with a 1D array.
    weights = new float[inputCount*outputCount];
//    weights

    //    randomizeWeights();
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



void Level::randomizeWeights(){
//    for(int i=0; i<weights.length()){
//
//    }
//    std::cout<<" \n";
}