#include "AiGrid.hpp"



class Level{
    AiGrid grid;
public:
    float *input;
    float *output;
    float *bias;
    int inputCount;
    int outputCount;
public:
    Level();
    Level(int inputCount, int outputCount);
    ~Level();
    void Randomize();

    void FeedForward(float givenInputs[]);

};

void Level::Randomize() {
    grid.randomizeWeights();
    for(int i = 0; i< sizeArray(bias); i++){
        bias[i] = get_random(-1, 1);
    }
}

Level::Level():grid(0,0){}

Level::Level(int inputCount, int outputCount) : grid(inputCount, outputCount){
    input = new float[inputCount];
    output = new float[outputCount];
    bias = new float[outputCount];
    this->inputCount = inputCount;
    this->outputCount = outputCount;

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

void Level::FeedForward(float givenInputs[]) {

    for(int appointInput = 0; appointInput < inputCount; appointInput++){
        input[appointInput] = givenInputs[appointInput];
    }

    for(int currentOutput = 0; currentOutput < outputCount; currentOutput++) {
        float sum = 0;
        for(int currentInput = 0; currentInput < inputCount; currentInput++){
            sum+=input[currentInput]*grid.at(currentInput, currentOutput);
        }
        if(sum+bias[currentOutput]>0){
            output[currentOutput] = 1;
        } else {
            output[currentOutput] = 0;
        }
    }
    for(int i = 0; i < outputCount; i++){
        std::cout<<output[i]<<"  "<<"\n";
    }
}

class NeuralNetwork{
    Level* levels[];
private:

public:
    NeuralNetwork(int neuronCount[]);
    ~NeuralNetwork():
};
NeuralNetwork::NeuralNetwork(int neuronCount[]) {
    levels = new Level[int(sizeArray(neuronCount)-1)];
    for(int i = 0; i< sizeArray(neuronCount)-1; i++){
        levels[i] = Level(neuronCount[i], neuronCount[i+1]);
    }

}

NeuralNetwork::~NeuralNetwork() {

}