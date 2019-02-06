#ifndef POPULATION_H
#define POPULATION_H

#include "individual.h"

class Population{

    private:
        vector<Individual> individuals;
        int seed;

    public:

         Population();

         Population(int seed, int individualsNum,Data data);

         Population(vector<Individual> individuals);

         vector<Individual> getIndividuals();

         void setIndividuals(vector<Individual> individuals);

         void setIndividual(Individual individual, int position);

         Individual getIndividual(int position);

         int getSeed();

         void setIndividualCost(int position, int newCost);

         Individual getBestIndividual();

         int getSize();

         void setSeed(int newSeed);

         int calculatePoblationCost();

         void print();

         void sortPopulation();


};

#endif // POPULATION_H
