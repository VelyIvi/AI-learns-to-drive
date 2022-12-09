class Level{
private:



public:
    Level(int inputCount, int outputCount){
        float input[inputCount];
        float output[outputCount];
        float bias[outputCount];

        std::vector<std::vector<float>> weights;
        weights.clear();
        for(int i=0;i<inputCount;i++){
            if(weights.size() < i+1){weights.push_back({});};
            for(int e=0;e<outputCount;e++){
                weights.at(i).push_back(0.5f);
            }
        }
    }
    ~Level(){
        std::cout<<"Called Neural Network Level destructor\n";
    }
};