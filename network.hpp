#include "AiGrid.hpp"

double sigmoidSmaller(double x) {
    return 2.0 / (1.0 + exp(-x)) - 0.5;
}
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}


double tanh(double x) {
    return (exp(2*x)-1)/(exp(2*x)+1);
}
class Layer{
public:
    std::vector<float> input;
    std::vector<float> output;
    std::vector<float> bias;
public:
    AiGrid grid;
    Layer(int inputCount, int outputCount);
    ~Layer();
    void Randomize();

    std::vector<float> feedForwardLinear(std::vector<float> givenInputs);

    std::vector<float> feedForwardSigmoid(std::vector<float> givenInputs);
};

void Layer::Randomize() {
    grid.randomizeWeights();
    for(float & currentBias : bias){
        currentBias = get_random(-1, 1);
    }
}

Layer::Layer(int inputCount, int outputCount) : grid(inputCount, outputCount){

    input = std::vector<float>(inputCount);

    output = std::vector<float>(outputCount);
    bias = std::vector<float>(outputCount);
    Randomize();
}

Layer::~Layer(){
//    std::cout<<"Called Layer destructor\n";
}
std::vector<float> Layer::feedForwardSigmoid(std::vector<float> givenInputs) {
    for(int appointInput = 0; appointInput < input.size(); appointInput++){
        input.at(appointInput) = givenInputs.at(appointInput);
    }

    for(int currentOutput = 0; currentOutput < output.size(); currentOutput++) {
        float sum = 0;
        for(int currentInput = 0; currentInput < input.size(); currentInput++){
            sum+=input.at(currentInput)*grid.at(currentInput, currentOutput);
        }
        output.at(currentOutput) = sigmoidSmaller(sum + bias.at(currentOutput));
    }
    return output;
}

std::vector<float> Layer::feedForwardLinear(std::vector<float> givenInputs) {
    for(int appointInput = 0; appointInput < input.size(); appointInput++){
        input.at(appointInput) = givenInputs.at(appointInput);
    }

    for(int currentOutput = 0; currentOutput < output.size(); currentOutput++) {
        float sum = 0;
        for(int currentInput = 0; currentInput < input.size(); currentInput++){
            sum+=input.at(currentInput)*grid.at(currentInput, currentOutput);
        }
        if(sum+bias.at(currentOutput)>0){
            output.at(currentOutput) = 1;
        } else {
            output.at(currentOutput) = 0;
        }
    }
    return output;
}
class NeuralNetwork {
private:
public:
    std::vector<Layer> layers;
    explicit NeuralNetwork(std::vector<int> layerSizes);
    void Mutate(float amount);
    void Randomize();

//    NeuralNetwork(const NeuralNetwork & copyNN);

    std::vector<float> feedForward(std::vector<float> input);
    std::vector<float> getOutput(std::vector<float> input);
};

void  NeuralNetwork::Randomize() {
    for(Layer & currentLevel: layers){
        currentLevel.Randomize();
    }
}

void NeuralNetwork::Mutate(float amount = 1) {
    for(Layer & currentLevel: layers){
        for(float & currentBias: currentLevel.bias) {
            currentBias = lerp(currentBias, get_random(-1,1), amount);
        }
    }

    for(Layer & currentLevel: layers){
        for(float & currentValue: currentLevel.grid.table) {
            currentValue = lerp(currentValue, get_random(-1,1), amount);
        }
    }
}


NeuralNetwork::NeuralNetwork(std::vector<int> layerSizes) {
    if(layerSizes.size()<2)
        throw std::invalid_argument("layerSizes must contain at least 2 elements");
    for (int i = 0; i < layerSizes.size() - 1; i++) {
        layers.emplace_back(layerSizes.at(i), layerSizes.at(i+1));
    }
}
//NeuralNetwork::NeuralNetwork(const NeuralNetwork & copyNN) {
//    std::cout<<"e\n";
//}

std::vector<float> NeuralNetwork::feedForward(std::vector<float> input) {
    std::vector<float> currentOutput = std::move(input);
    for (int i = 0;i<layers.size();i++) {
        if(i != layers.size()-1) { // if not output layer
            currentOutput = layers.at(i).feedForwardSigmoid(currentOutput);
        } else {
            currentOutput = layers.at(i).feedForwardLinear(currentOutput);
        }
    }
    return currentOutput;
}

std::vector<float> NeuralNetwork::getOutput(std::vector<float> input) {
    return feedForward(std::move(input));
}

