#include "geneticalgorithm.h"
#include "optimizer.h"
#include <algorithm>

#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(Data data, int seed){

     this->data = data;
     this->mutationProbability = 0.01;
     this->selectionProbability = 0.8;
     this->seed = seed;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(Data data, Population population, int seed){

     this->data = data;
     this->population = population;
     this->mutationProbability = 0.01;
     this->selectionProbability = 0.8;
     this->seed = seed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::newLamarckGeneration(int iterations){

    Individual newIndividual;
    Optimizer optimizer = Optimizer();

    // Iteramos sobre la población
    for(int i = 0; i < this->population.getSize(); ++i){

        // Generamos la mejor solución utilizando el algoritmo de búsqueda local
        newIndividual = optimizer.localSearch_1(this->data,this->population.getIndividual(i),iterations);

        // Establece el mejor coste del individuo, que en la versión Lamarckiana coincide con su coste.
        newIndividual.setBestCost(newIndividual.getCost());

        // Suplantamos el individuo actual de la población por ese mejor.
        this->population.setIndividual(newIndividual,i);
    }

    this->sort();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Data GeneticAlgorithm::getData(){

    return this->data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setData(Data newData){

    this->data = newData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Population GeneticAlgorithm::getPopulation(){

    return  this->population;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GeneticAlgorithm::setPopulation(Population newPopulation){

     this->population = newPopulation;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::sort(){

    this->population.sortPopulation();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Individual GeneticAlgorithm::getBestIndividual(){

    return this->population.getIndividual(0);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Individual GeneticAlgorithm::getWorstIndividual(){

    return this->population.getIndividual(this->population.getSize()-1);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float GeneticAlgorithm::getSelectionProbability(){

    return this->selectionProbability;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setSelectionProbability(float newSelectionProbability){

    if(newSelectionProbability >= 0 && newSelectionProbability<=1){
        this->selectionProbability = newSelectionProbability;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

float GeneticAlgorithm::getMutationProbability(){

    return this->mutationProbability;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setMutationProbability(float newMutationProbability){

    if(newMutationProbability >= 0 && newMutationProbability<=1){
        this->mutationProbability = newMutationProbability;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int  GeneticAlgorithm::getSeed(){

    return this->seed;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setSeed(int newSeed){

    if(newSeed > 0){
        this->seed = newSeed;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

Individual GeneticAlgorithm::binaryTournamet(Individual individual1, Individual individual2){

    // Si el individuo 1 es mejor que el individuo 2
    if(individual1 < individual2)
        return individual1;
    else
        return individual2;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::generateParentsGeneration(){

    // Número de selecciones que se realizarán en función de la probabilidad de selección.
    int selectionNum = (int) (this->selectionProbability * this->population.getSize());

    // Vector donde se almacerán los individuos de la nueva generación
    vector<Individual> newIndividuals;

    // Números aleatorios de selección
    int random1,random2;

    Individual winner;

    for(int i = 0; i < selectionNum; ++i){
        random1 = rand() % this->population.getSize();
        random2 = rand() % this->population.getSize();

        winner = this->binaryTournamet(this->population.getIndividual(random1),this->population.getIndividual(random2));
        newIndividuals.push_back(winner);
    }

    // Si aún no se ha llenado la población, se introducen individuos hasta completarla
    if(newIndividuals.size() < this->population.getSize() ){

        // Introducimos al peor individuo para añadir más diversidad. Dicho individuo se sitúa al final
        // de la población, ya que la población está ordenada.
        newIndividuals.push_back(this->population.getIndividual(this->population.getSize()-1));

        // Calculamos el número de los n individuos restantes
        int remainingIndividualsNum = this->population.getSize() - newIndividuals.size();

        // Introducimos los primero n individuos mejores hasta completar la población
        for(int i = 0; i < remainingIndividualsNum; ++i ){
            newIndividuals.push_back(this->population.getIndividual(i));
        }

    }

    // Actualizamos la población a esta nueva generación de individuos.
    this->population.setIndividuals(newIndividuals);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::generateChildrenGeneration(){

    // Tamaño del individuo
    int individualSize = this->population.getIndividual(0).getSize();

    // Mitad del individuo
    //int individualCenter = (int) ( individualSize / (rand() % (individualSize-2)) );
      int individualCenter = (int) ( individualSize / 2);

    vector<Individual> newIndividuals;
    vector<int> solutionChild1;
    vector<int> solutionChild2;

    int populationSize= this->population.getSize();
    int solutionSize = this->population.getIndividual(0).getSize();

    ///////////////////////////////////////////////////////
    // Operador de cruce : Combinación de dos permutaciones
    ///////////////////////////////////////////////////////

   for(int i = 0; i < populationSize  ; i+=2){

        // Limpiamos los vectores de soluciones
        solutionChild1.clear();
        solutionChild2.clear();

        Individual father1 = this->population.getIndividual(i);
        Individual father2 = this->population.getIndividual(i+1);

        // Copiamos la primera mitad del primer individuo
        for(int j = 0; j < individualCenter; ++j){
            solutionChild1.push_back(father1.getVectorSolutions().at(j));
            solutionChild2.push_back(father2.getVectorSolutions().at(j));
        }

        int index = individualCenter;

        // Mientras que no se haya completado el vector
        while(solutionChild1.size() < solutionSize){

            // Comprobamos si la fábrica( o flujo) del segundo padre en la posición j ya está contenida en la solución.
            bool solutionAlreadyExist =find(solutionChild1.begin(), solutionChild1.end(), father2.getVectorSolutions().at(index)) != solutionChild1.end();

            // Si no está contenida, se añade
            if(solutionAlreadyExist == false){
                solutionChild1.push_back(father2.getVectorSolutions().at(index));
            }

            // Incrementamos en uno módulo su tamaño nuestra variable iteradora del padre
            index = (index + 1) % solutionSize;
        }

        index = individualCenter;

        // Mismo proceso para el hijo 2
        while(solutionChild2.size() < solutionSize){

            // Comprobamos si la fábrica( o flujo) del primer padre en la posición j ya está contenida en la solución.
            bool solutionAlreadyExist =find(solutionChild2.begin(), solutionChild2.end(), father1.getVectorSolutions().at(index)) != solutionChild2.end();

            // Si no está contenida, se añade
            if(solutionAlreadyExist == false){
                solutionChild2.push_back(father1.getVectorSolutions().at(index));
            }

            // Incrementamos en uno módulo su tamaño nuestra variable iteradora del padre
            index = (index + 1) % solutionSize;
        }

        // Creamos el primer individuo que se ha generado en el cruce
        Individual newIndividual = Individual(this->data,this->seed,solutionChild1);
        // Creamos el segundo individuo que se ha generado en el cruce
        Individual newIndividual2 = Individual(this->data,this->seed,solutionChild1);

        //Añadimos los individuos a la nueva población
        newIndividuals.push_back(newIndividual);
        newIndividuals.push_back(newIndividual2);
   }

   Population childrenPopulation = Population(newIndividuals);

   this->population = childrenPopulation;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::mutate(int position){

    int random1,random2;
    // Obtenemos el tamaño del individuo
    int individualSize = this->population.getIndividual(0).getSize();

    // Generamos dos números aleatorios que no sean iguales
    do{
        random1 = rand()%individualSize;
        random2 = rand()%individualSize;

    }while(random1==random2);

    // Se obtiene las soluciones del individuo seleccionado
    vector<int> individualSolutions = this->population.getIndividual(position).getVectorSolutions();

    // Realizamos una permutación en la posición aleatoria.
    int aux = individualSolutions.at(random1);
    individualSolutions.at(random1) = individualSolutions.at(random2);
    individualSolutions.at(random2) = aux;

    // Actualizamos la mutación del individuo en nuestra población
    this->population.getIndividual(position).setVectorSolutions(individualSolutions);

    // Recalculamos el coste para dicho individuo
    this->population.getIndividual(position).calculateCost(this->data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////


int GeneticAlgorithm::getGenerationNumber(){

    return this->generationNumber;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setGenerationNumber(int newGenerationNumber){

    if(newGenerationNumber > 0)
        this->generationNumber = newGenerationNumber;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
