#include "population.h"
#include <cstdlib>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Population::Population(int seed, int individualsNum, Data data){

    this->generationNumber = 0;
    this->seed = seed;

    srand(seed);

    unsigned int seedRange = 4294967295;

    for(int i = 0; i < individualsNum; ++i){

        int individualSeed = rand() % seedRange;
        this->individuals.push_back(Individual(data,individualSeed));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Population::Population(vector<Individual> newIndividuals){

    this->generationNumber = 0;
    this->individuals = newIndividuals;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Individual> Population::getIndividuals(){

    return this->individuals;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::setIndividuals(vector<Individual> newIndividuals){

    this->individuals = newIndividuals;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::setIndividual(Individual newIndividual, int position){

    if(position >= 0 && position < this->individuals.size()){
        individuals[position] = newIndividual;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Individual Population::getIndividual(int position){

    if(position >= 0 && position < this->individuals.size()){
        return this->individuals[position];
    }
    else{
       return Individual();
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Population::getGenerationNumber(){

    return this->generationNumber;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::setGenerationNumber(int newGenerationNumber){

    if(newGenerationNumber >= 0){
        this->generationNumber = newGenerationNumber;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Population::getSeed(){

    return this->seed;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Population::getSize(){

    return this->individuals.size();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::setSeed(int newSeed){

    if(newSeed > 0){
        this->seed = newSeed;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::print(){

    cout << "Tamaño de la población: " << this->getSize() <<endl;
    cout << "Número de generación: " << this->generationNumber<<endl;
    cout << "Semilla de la población: " << this->seed <<endl;

    cout << "Imprimiendo los individuos de la población" <<endl<<endl;
    for(int i = 0; i < this->getSize(); ++i){
        cout << "Individuo " << i <<endl;
        cout << "-----------------" <<endl;

        this->individuals[i].print();

        cout << "-----------------" <<endl;
        cout << "Coste = " << this->individuals[i].getCost();
        cout << endl <<endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Population::calculatePoblationCost(){

    int accumulator = 0;

    for(int i = 0; i < this->getSize(); ++i){
        accumulator += this->individuals[i].getCost();
    }

    return accumulator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::sortPopulation(){

    Individual individualAux;

    for(int i = 0; i < this->getSize(); ++i ){
        for(int j = 0; j < this->getSize()-1; ++j){
            if( this->individuals[j] > this->individuals[j+1] ){
                individualAux = this->individuals[j];
                this->individuals[j] = this->individuals[j+1];
                this->individuals[j+1] = individualAux;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Population::newLamarckGeneration(){

    for(int i = 0; i < this->getSize(); ++i){



    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
