#include <iostream>
#include "data.h"
#include "population.h"
#include "optimizer.h"

#include <vector>

using namespace std;

int main(){

    const int populationSeed = 2;
    const int individualsNum = 60;
    const int generationNum = 60000;
    const int numIterations = 60000;


    Data data = Data("chr22a.dat");

    Population population = Population(populationSeed, individualsNum, data);

    population.sortPopulation();

    for( int i = 0; i < population.getSize(); ++i){
        cout << population.getIndividual(i).getCost() << endl;
    }



    Optimizer optimizer = Optimizer();

    Individual result = optimizer.localSearch_1(data,population.getIndividual(4) ,numIterations);

    cout << "El coste final es --> " << result.getCost() << endl;











    /*  TEST DE COMPROBAR FUNCIÓN AJUSTE Y CALCULAR COSTE DE UN INDIVIDUO

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

    */
    return 0;
}
