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
        int bestCost;



    public:

        Individual();

        Individual(Data data, int seed);

        Individual(Data data, int seed, vector<int> solutions);

        void initialize();

        void print();

        void calculateCost(Data &data);

        int getCost();

        void setCost(int cost);

        int getSeed();

        void setSeed(int seed);

        int getSize();

        int getBestCost();

        void setBestCost(int newBestCost);

        vector<int> getVectorSolutions();

        void setVectorSolutions(int value, int position);

        void setVectorSolutions(vector<int> newSolutions);

        void exchange(int position1, int position2);

        bool operator<(Individual &compareIndividual);

        bool operator>(Individual &compareIndividual);

        bool operator==(Individual &compareIndividual);

        void adjustCost(int position1, int position2, Data &data);

};

#endif // INDIVIDUAL_H
