#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include "data.h"

using namespace std;

class Individual{

    private:

        vector<int> solutions;
        int size;
        int seed;
        int cost;



    public:

        Individual();

        Individual(Data data, int seed);

        void initialize();

        void print();

        void calculateCost(Data &data);

        int getCost();

        void setCost(int cost);

        int getSeed();

        void setSeed(int seed);

        vector<int> getVectorSolutions();

        void setVectorSolutions(int value, int position);

        bool operator<(Individual &compareIndividual);

        bool operator>(Individual &compareIndividual);

        bool operator==(Individual &compareIndividual);

};

#endif // INDIVIDUAL_H
