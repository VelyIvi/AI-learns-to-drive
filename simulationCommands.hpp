
void startSim(){
    car.clear();
    aliveCar.clear();

    currentGeneration = 0;
    realTime = 0;
    simTime = 0;
    currentSimTime = 0;

    for(int x = 0; x<100; x++){
        car.emplace_back(*map->startPos, *map->startRot, map->map_points, map->map_check);
        aliveCar.push_back(x);
    }
    bestCar = &car.at(0);
    selectedCar = &car.at(0);

}
void retrySim(){
    float mut = mutationValue;
    currentGeneration++;
    currentSimTime = 0;
    for(int x = 0; x<car.size(); x++){
        aliveCar.push_back(x);
    }
    NeuralNetwork bestSavedNN = bestCar->nn;
    for(int i = 0; i<car.size(); i++){
//        if(i < car.size()/3*2) {
        car.at(i).nn = bestSavedNN;

        if (i != 0) {
            car.at(i).nn.Mutate(mut * float(float(i) / car.size()));
        }
//        } else {
//            car.at(i).nn.Randomize();
//        }
//        car.at(i).nn.Randomize();

        car.at(i).ResetValues(*map->startPos, *map->startRot, true);
    }

    bestCar = &car.at(0);
    selectedCar = &car.at(0);


}

void ResetGen(){
    aliveCar.clear();
    currentSimTime = 0;
    for(int x = 0; x<car.size(); x++){
        aliveCar.push_back(x);
        car.at(x).ResetValues(*map->startPos, *map->startRot, true);
    }
}


void CheckSim(){
    if(aliveCar.empty()){
        retrySim();
        return;
    }
    for(int i = 0; i < aliveCar.size(); i++){
        if(car.at(aliveCar.at(i)).points > bestCar->points){
            bestCar = &car.at(aliveCar.at(i));
        }
        if(!car.at(aliveCar.at(i)).alive){
            aliveCar.erase(aliveCar.begin()+i);
            return;
        } else if(car.at(aliveCar.at(i)).laps>=3){
            aliveCar.erase(aliveCar.begin()+i);
            retrySim();
//            car.at(aliveCar.at(i)).alive = false; ////crash
            return;

        }
    }


}