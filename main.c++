#include <iostream>
#include "data.h"
#include "population.h"

#include <vector>

using namespace std;

int main(){

    const int populationSeed = 2;
    const int individualsNum = 60;
    const int generationNum = 60000;


    Data data = Data("chr22a.dat");

    /*Individual individual = Individual(data, populationSeed);
    Individual individual2 = Individual(data, populationSeed);

    individual.print();

    individual2.print();*/

    Population population = Population(populationSeed, individualsNum, data);

    population.print();

    cout << endl << endl << endl;



    Individual individual = population.getIndividual(59);

    cout << "Coste inicial = " << population.getIndividual(59).getCost() << endl;

    individual.exchange(0,15);
    individual.adjustCost(0,15,data);

    cout << "Coste final ajustado = " << individual.getCost() << endl;

    individual.calculateCost(data);

    cout << "Coste final calculado= " << individual.getCost() << endl;


    return 0;
}
