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

class Level{
    AiGrid grid;
private:
    float *input;
    float *output;
    float *bias;
    int maxInputs;
    int maxOutputs;
public:
    Level(int inputCount, int outputCount);
    ~Level();
    void Randomize();



    void FeedForward(float givenInputs[]){
        for(int appointInput = 0; appointInput<maxInputs; appointInput++){
            input[appointInput] = givenInputs[appointInput];
        }

        for(int currentOutput = 0; currentOutput<maxOutputs; currentOutput++) {
            float sum = 0;
            for(int currentInput = 0; currentInput<maxInputs; currentInput++){
                sum+=input[currentInput]*grid.at(currentInput, currentOutput);
            }
            if(sum+bias[currentOutput]>0){
                output[currentOutput] = 1;
            } else {
                output[currentOutput] = 0;
            }
        }
        return;

    }
};

void Level::Randomize() {
    grid.randomizeWeights();
    for(int i = 0; i< sizeArray(bias); i++){
        bias[i] = get_random(-1, 1);
    }
}


Level::Level(int inputCount, int outputCount) : grid(inputCount, outputCount){
    input = new float[inputCount];
    output = new float[outputCount];
    bias = new float[outputCount];
    maxInputs = inputCount;
    maxOutputs = outputCount;

    Randomize();
}

Level::~Level(){
    delete[] input;
    delete[] output;
    delete[] bias;

    input = nullptr;
    output = nullptr;
    bias = nullptr;

    std::cout<<"Called Neural Network Level destructor\n";
}