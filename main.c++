#include <iostream>
#include "data.h"
#include "geneticalgorithm.h"

using namespace std;

int main(){

    const int populationSeed = 2;
    const int geneticAlgorithmSeed = 2;
    const int individualsNum = 60;
    const int generationNum = 60000;
    const int numIterations = 60000;


    Data data = Data("chr22a.dat");

    Population population = Population(populationSeed, individualsNum, data);

    population.sortPopulation();

    GeneticAlgorithm geneticAlgorithm = GeneticAlgorithm(data,population,geneticAlgorithmSeed);

    geneticAlgorithm.newLamarckGeneration(numIterations);


   for( int i = 0; i < geneticAlgorithm.getPopulation().getSize(); ++i){
       cout << geneticAlgorithm.getPopulation().getIndividual(i).getCost() << endl;
   }
   geneticAlgorithm.generateParentsGeneration();

   geneticAlgorithm.generateChildrenGeneration();

   /* PRUEBA TORNEO BINARIO
    Individual i1 = geneticAlgorithm.getPopulation().getIndividual(0);
    Individual i2 = geneticAlgorithm.getPopulation().getIndividual(1);
    Individual i3 = geneticAlgorithm.getPopulation().getIndividual(2);

    Individual i,j;

    i = geneticAlgorithm.binaryTournamet(i1,i2);
    j = geneticAlgorithm.binaryTournamet(i2,i3);

    cout << endl << endl;
    cout << "Mejor 1 = " << i.getCost() <<endl;

    cout << endl;
    cout << "Mejor 2 = " << j.getCost() <<endl;
    */

   /*   MOSTRAR Y MODIFICAR PROBABILIDAD DE SELECCIÓN Y MUTACIÓN
   cout <<endl << endl;

   cout << "Probabilidad de mutación = " << geneticAlgorithm.getMutationProbability() << endl;
   cout << "Probabilidad de selección = " << geneticAlgorithm.getSelectionProbability() << endl;

   geneticAlgorithm.setMutationProbability(0.02);
   geneticAlgorithm.setSelectionProbability(0.9);

   cout << "Probabilidad de mutación = " << geneticAlgorithm.getMutationProbability() << endl;
   cout << "Probabilidad de selección = " << geneticAlgorithm.getSelectionProbability() << endl;

    */

   /* for( int i = 0; i < geneticAlgorithm.getPopulation().getSize(); ++i){



        cout << geneticAlgorithm.getPopulation().getIndividual(i).getCost() << endl;
    }*/

    // VOY A PROBAR A MOSTRAR LOS COSTES ANTES DE LAMARCK Y DESPUÉS















    /* TEST PARA LA POBLACIÓN

    Population population = Population(populationSeed, individualsNum, data);

    population.sortPopulation();

    for( int i = 0; i < population.getSize(); ++i){
        cout << population.getIndividual(i).getCost() << endl;
    }

    cout << endl << endl << endl;

    population.newLamarckGeneration(numIterations);
    population.sortPopulation();

    for( int i = 0; i < population.getSize(); ++i){
        cout << population.getIndividual(i).getCost() << endl;
    }

    */

    /* TEST DE LA BÚSQUEDA LOCAL

    for( int i = 0; i < population.getSize(); ++i){
        cout << population.getIndividual(i).getCost() << endl;
    }

    Optimizer optimizer = Optimizer();

    Individual result = optimizer.localSearch_1(data,population.getIndividual(4) ,numIterations);

    cout << "El coste final es --> " << result.getCost() << endl;
    */




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
