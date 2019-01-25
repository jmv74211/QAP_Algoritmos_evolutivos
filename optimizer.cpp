#include "optimizer.h"

#include <iostream>

using namespace std;

Optimizer::Optimizer(){}


Individual Optimizer::localSearch_1(Data &data,Individual firstIndividual, int numIterations){

       // Genera una solución/individuo inicial
       Individual individual = firstIndividual;
       // Inicializa la mejor solución/individuo
       Individual bestIndividual = firstIndividual;

       int iteration=0;
       bool improve = false;

       do{
           cout << iteration << endl;
           // Inicializamos la bandera de mejora
           improve = false;

           // Generamos el vecino que es una copia del individuo actual.
           Individual neighbour = Individual(individual);

           // Recorremos la solución
           for(int i= 0; i < individual.getSize(); ++i){
               for(int j =i+1; j < individual.getSize(); ++j){
                   // Intercambiamos la posición de las fábricas
                   neighbour.exchange(i,j);
                   // Recalculamos el nuevo coste
                   neighbour.adjustCost(i,j,data);

                   // Si mejora el coste del individuo actual
                   if(neighbour < individual){
                        individual = neighbour;
                   }
                   // Si el nuevo vecino es la mejor solución hasta el momento
                   if(individual < bestIndividual){
                       bestIndividual = individual;
                       improve = true;
                   }
               }
           }

           iteration++;

       }while( (numIterations > iteration) && improve);


       return bestIndividual;

}
