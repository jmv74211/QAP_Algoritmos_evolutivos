#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H


#include "population.h"

class GeneticAlgorithm{

    private:
        Population population;
        Data data;
        float selectionProbability;
        float mutationProbability;
        int seed;
        int generationNumber;

    public:

         GeneticAlgorithm();

         GeneticAlgorithm(Data data, int seed);

         GeneticAlgorithm(Data data, Population population, int seed);

         void newLamarckGeneration(int iterations);

         void sort();

         Individual binaryTournamet(Individual individual1, Individual individual2);

         void generateParentsGeneration();

         void generateChildrenGeneration();

         void mutate(int position);



        // GETTERS Y SETTERS

         Data getData();

         void setData(Data newData);

         Population getPopulation();

         void setPopulation(Population newPopulation);

         float getSelectionProbability();

         void setSelectionProbability(float newSelectionProbability);

         float getMutationProbability();

         void setMutationProbability(float newMutationProbability);

         int getSeed();

         void setSeed(int newSeed);

         int getGenerationNumber();

         void setGenerationNumber(int newGenerationNumber);

         Individual getBestIndividual();

         Individual getWorstIndividual();



};

#endif // GENETICALGORITHM_H
