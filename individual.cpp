#include "individual.h"
#include <cstdlib>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Individual::Individual(){

    this->seed = 1;
    this->size = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Individual::Individual(Data data, int seed){

    this->seed = seed;

    this->size = data.getSize();

    this->initialize();

    this->calculateCost(data);

    this->bestCost = this->cost;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Individual::Individual(Data data, int seed, vector<int> solutions){

    this->seed = seed;

    this->size = data.getSize();

    this->solutions = solutions;

    this->calculateCost(data);

    this->bestCost = this->cost;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::calculateCost(Data &data){

    int accumulator = 0;

    for(int i = 0; i < this->size; ++i){
        for(int j = 0; j < this->size; ++j){
            if(i!=j){
                accumulator += data.getFactory(i,j)*data.getDistance(this->solutions[i],this->solutions[j]);
            }
        }
    }

    this->setCost(accumulator);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::initialize(){

    int exchanger = 0;
    int random = 0;
    int max = (this->size-1);
    int min = 0;

    srand(this->seed);

    for(int i = 0; i < this->size ; ++i){
        this->solutions.push_back(i);
    }

    for(unsigned i = 0; i < this->solutions.size(); ++i){
        for(unsigned j = 0; j < max; ++j){
            min = j;
            random = rand() % max;
            exchanger = this->solutions[i];
            this->solutions[i] = this->solutions[random];
            this->solutions[random] = exchanger;
        }
    }

    this->size = this->solutions.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::print(){

    for(int i = 0; i < this->size; ++i ){
        cout << this->solutions[i] << " ";
    }
    cout <<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Individual::getCost(){

    return this->cost;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::setCost(int newCost){

    if(newCost > 0)
        this->cost = newCost;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Individual::getSeed(){

    return this->seed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::setSeed(int newSeed){

    if(newSeed > 0)
        this->seed = newSeed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Individual::getSize(){

    return this->size;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> Individual::getVectorSolutions(){

    return this->solutions;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Individual::getBestCost(){

    return this->bestCost;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::setBestCost(int newBestCost){

    if(newBestCost >=0){
        this->bestCost = newBestCost;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Importante actualizar el coste tras llamar a esta función
void Individual::setVectorSolutions(int value, int position){
    if(position >= 0 && value >= 0)
        this->solutions[position] = value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::exchange(int position1, int position2){

    if(position1 >=0 && position2 >= 0 && position1 < this->size && position2 < this->size){
        int aux = this->solutions[position1];
        this->solutions[position1] = this->solutions[position2];
        this->solutions[position2] = aux;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Individual::operator<(Individual &compareIndividual){

    return (this->cost < compareIndividual.getCost());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Individual::operator>(Individual &compareIndividual){

    return (this->cost > compareIndividual.getCost());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Individual::operator==(Individual &compareIndividual){

    return (this->cost == compareIndividual.getCost());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Individual::adjustCost(int position1, int position2, Data &data){

    int accumulator = 0;

    for(int i = 0; i < this->size; ++i){
        if( i != position1 && i != position2){
            accumulator += data.getFactory(position1,i) * (data.getDistance(this->solutions[position2],this->solutions[i]) - data.getDistance(this->solutions[position1],this->solutions[i]));
            accumulator += data.getFactory(position2,i) * (data.getDistance(this->solutions[position1],this->solutions[i]) - data.getDistance(this->solutions[position2],this->solutions[i]));

            accumulator += data.getFactory(i,position1) * (data.getDistance(this->solutions[i],this->solutions[position2]) - data.getDistance(this->solutions[i],this->solutions[position1]));
            accumulator += data.getFactory(i,position2) * (data.getDistance(this->solutions[i],this->solutions[position1]) - data.getDistance(this->solutions[i],this->solutions[position2]));
        }
     }

    this->cost = this->cost + accumulator*(-1);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Individual::setVectorSolutions(vector<int> newSolutions){

    this->solutions = newSolutions;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
