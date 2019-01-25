#ifndef POPULATION_H
#define POPULATION_H

#include "individual.h"

class Population{

    private:
        int generationNumber;
        vector<Individual> individuals;
        int seed;


    public:

         Population(int seed, int individualsNum,Data data);

         Population(vector<Individual> individuals);

         vector<Individual> getIndividuals();

         void setIndividuals(vector<Individual> individuals);

         void setIndividual(Individual individual, int position);

         Individual getIndividual(int position);

         int getGenerationNumber();

         void setGenerationNumber(int newGenerationNumber);

         int getSeed();

         int getSize();

         void setSeed(int newSeed);

         int calculatePoblationCost();

         void print();

         void sortPopulation();

         void newLamarckGeneration();
};

#endif // POPULATION_H




/*

//Individual::Individual(int size){

        // Crear solución aleatoria.
        // Crear método para calcular la función de coste
        // Calcular incremento del coste cuando se cambia de solución
        // Función para intercambiar dos valores. para mutacion SWAP

        // Añadir atributo coste
//}

// Algoritmo genético:

    /*
        - Declarate vector de individuos inicializado aleatoriamente
        - Probabilidad de cruce, mutación
*/


//

// Operador de selección
/*
    - Selección por torneo binario:
        Generar un valor aletorio.
        Se genera otro valor aleatorio distinto del anterior (si es mismo recalcular)
        Comparar los costes

    -

*/
