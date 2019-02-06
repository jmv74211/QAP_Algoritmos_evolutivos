#include "geneticalgorithm.h"
#include "optimizer.h"
#include <algorithm>

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(Data data, int seed){

     this->data = data;
     this->mutationProbability = 0.001;
     this->selectionProbability = 0.8;
     this->seed = seed;
     this->bestIndividual = Individual(data,seed);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeneticAlgorithm::GeneticAlgorithm(Data data, Population population, int seed){

     this->data = data;
     this->population = population;
     this->mutationProbability = 0.01;
     this->selectionProbability = 0.8;
     this->seed = seed;
     this->bestIndividual = population.getBestIndividual();
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

    // Si el mejor individuo de la generación es mejor que el mejor individuo general encontrado, se actualiza
    this->checkBestIndividual();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::newBaldwinGeneration(int iterations){

    Individual newIndividual;
    Optimizer optimizer = Optimizer();

    // Iteramos sobre la población
    for(int i = 0; i < this->population.getSize(); ++i){

        // Generamos la mejor solución utilizando el algoritmo de búsqueda local
        newIndividual = optimizer.localSearch_1(this->data,this->population.getIndividual(i),iterations);

        // Establecemos como mejor coste del individuo al de su vecino optimizado.
        int newCost = newIndividual.getCost();

        // Copiamos al mismo individuo para modificar solo su coste
        Individual individualCopy = Individual(this->data, this->seed, this->population.getIndividual(i).getVectorSolutions());
        individualCopy.setCost(newCost);

        this->population.setIndividual(individualCopy,i);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::checkBestIndividual(){

    // Obtenemos el mejor individuo de la generación
    Individual bestIndividualGeneration = this->population.getBestIndividual();

    // Si el mejor individuo de la generación es mejor que el mejor individuo general encontrado, se actualiza
    if( bestIndividualGeneration< this->bestIndividual)
        this->bestIndividual = bestIndividualGeneration;
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
    // Cogemos dos invividuos aleatoriamente, y se selecciona uno por torneo. Ese vencedor se añade a la población
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

    // Si el mejor individuo de la generación es mejor que el mejor individuo general encontrado, se actualiza
    this->checkBestIndividual();
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
    vector<bool> fatherHasBeenCrossed; // Vector para comprobar si los padres ya se han cruzado
    int random1,random2;
    bool selected;

    int populationSize= this->population.getSize();
    int solutionSize = this->population.getIndividual(0).getSize();

    ///////////////////////////////////////////////////////
    // Operador de cruce : Combinación de dos permutaciones
    ///////////////////////////////////////////////////////

   for(int i = 0; i < populationSize  ; i+=2){

       // Inicializamos el vector de booleanos
       for(int j = 0 ; j < populationSize; ++j){
            fatherHasBeenCrossed.push_back(false);
       }

        // Limpiamos los vectores de soluciones
        solutionChild1.clear();
        solutionChild2.clear();

        // Bandera para comprobar que se han seleccionado los padres
        selected = false;

        // Padres
        Individual father1;
        Individual father2;

        // Mientras no se haya seleccionado a los padres
        while(selected == false){

            // Se genera las índices de los padres de forma aleatoria
            random1 = rand()%populationSize;
            random2 = rand()%populationSize;

            // Escogemos dos padres diferentes
            if(random1 != random2){
                // Buscamos un padre que no haya sido usado
                while( fatherHasBeenCrossed.at(random1) == true){
                    random1 = (random1 + 1)%populationSize;
                }
                // Escogemos dicho padre
                father1 = this->population.getIndividual(random1);
                // Contamos a dicho padre como cruzado
                fatherHasBeenCrossed.at(random1) = true;

                // Buscamos un padre que no haya sido usado
                while( fatherHasBeenCrossed.at(random2) == true){
                    random2 = (random2 + 1)%populationSize;
                }
                // Escogemos dicho padre
                father2 = this->population.getIndividual(random2);
                fatherHasBeenCrossed.at(random2) = true;

                selected = true; // true para pasar a la siguiente iteración
            }
        }


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
        Individual newIndividual2 = Individual(this->data,this->seed,solutionChild2);

        //Añadimos los individuos al vector de individuos
        newIndividuals.push_back(newIndividual);
        newIndividuals.push_back(newIndividual2);
   }

   // Creamos una población con los nuevos individuos
   Population childrenPopulation = Population(newIndividuals);

   // Actualizamos la población con la nueva
   this->population = childrenPopulation;

   // Ordenamos la población
   this->sort();

   // Si el mejor individuo de la generación es mejor que el mejor individuo general encontrado, se actualiza
   this->checkBestIndividual();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::mutate(int position){

    cout << "El individuo está mutando..." << endl;

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
    //this->population.getIndividual(position).setVectorSolutions(individualSolutions);

    this->population.setIndividual(Individual(this->data, this->seed, individualSolutions), position);
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

Individual GeneticAlgorithm::getBestIndividual(){

    return this->bestIndividual;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::setBestIndividual(Individual newBestIndividual){

    this->bestIndividual = newBestIndividual;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Algoritmo que calcula al mejor vecino y reemplaza al individuo
void GeneticAlgorithm::lamarckEvolution(int generationIterations){

    const int searchAlgorithmIterations = 60; // Número de iteraciones máximas para el algoritmo de optimización local
    int randomNum; // Número aleatorio para la mutación
    int mutationNumber; // Número límite según la probabilidad de mutación
    double time; // Variable para medir el tiempo

    unsigned t0, t1;

    // Generamos el límite para el número aleatorio. Cuidamos no hacer la operación módulo 0
    if(this->mutationProbability != 0)
        mutationNumber= 1 / this->mutationProbability;
    else
        mutationNumber = 1;

    // Nombre del fichero de salida
    ofstream outfile ("logs/lamarckEvolution/log_"+ this->data.getFilename() +".txt");

    // Iteramos sobre el número de generaciones
    for(int i = 0; i < generationIterations; ++i){

        t0=clock();

        // Se calcula un número aleatorio comprendido entre 0 y el límite.
        randomNum = rand()%mutationNumber;

        // Se genera la población de lamarck(individuos optimizados según óptimo local y transformados)
        this->newLamarckGeneration(searchAlgorithmIterations);

        // Se genera la selección de los padres y se actualiza la población
        this->generateParentsGeneration();

        // Se actualiza la población con los hijos resultados de la combinación entre padres (2 padres = 2 hijos).
        this->generateChildrenGeneration();

        // Si por ejemplo el número aleatorio es 2, realizamos la mutación del individuo
        if(randomNum == 2){
            this->mutate( rand() % this->population.getSize() );
        }

        // Se comprueba si se ha mejorado la solución actual, en tal caso se actualiza
        this->checkBestIndividual();

        t1 = clock();
        time = (double(t1-t0)/CLOCKS_PER_SEC); // Calculamos el tiempo de ejecución en el cálculo de la nueva población

        // Se muestra la información resultante por pantalla
        cout << "Semilla = " <<  this->seed << " || Generación " << this->generationNumber << "|| Coste = " << this->getPopulation().getBestIndividual().getCost()
             << " || Mejor coste = " << this->getBestIndividual().getCost()  << " ||  Tiempo empleado = " << time
             << " || mejor solución = ";
        this->getBestIndividual().print();
        cout << endl;

        // Generamos un registro cada 10 generaciones
        if(i%10== 0){
            outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
                    <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;
        }
        // Incrementamos en uno el número de generaciones de la población del algoritmo.
        this->generationNumber++;
    }

    outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
            <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;

    outfile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Algoritmo que calcula utiliza al mejor vecino cercano pero sin reemplazar al individuo.
void GeneticAlgorithm::baldwinEvolution(int generationIterations){

    const int searchAlgorithmIterations = 60;
    int randomNum; // Número aleatorio para la mutación
    int mutationNumber; // Número límite según la probabilidad de mutación
    double time; // Variable para medir el tiempo

    unsigned t0, t1;

    // Generamos el límite para el número aleatorio. Cuidamos no hacer la operación módulo 0
    if(this->mutationProbability != 0)
        mutationNumber= 1 / this->mutationProbability;
    else
        mutationNumber = 1;

    // Nombre del fichero de salida
    ofstream outfile ("logs/baldwinEvolution/log_"+ this->data.getFilename() +".txt");

    // Iteramos sobre el número de generaciones
    for(int i = 0; i < generationIterations; ++i){

        t0=clock();

        // Se calcula un número aleatorio comprendido entre 0 y el límite.
        randomNum = rand()%mutationNumber;

        // Se genera la población de baldwin(Coste del mejor individuo vecino pero sin transformarse)
        this->newBaldwinGeneration(searchAlgorithmIterations);

        // Se genera la selección de los padres y se actualiza la población
        this->generateParentsGeneration();

        // Se actualiza la población con los hijos resultados de la combinación entre padres (2 padres = 2 hijos).
        this->generateChildrenGeneration();

        // Si por ejemplo el número aleatorio es 2, realizamos la mutación del individuo
        if(randomNum == 2){
            this->mutate( rand() % this->population.getSize() );
        }

        // Se comprueba si se ha mejorado la solución actual, en tal caso se actualiza
        this->checkBestIndividual();

        t1 = clock();
        time = (double(t1-t0)/CLOCKS_PER_SEC);

        // Se muestra la información resultante por pantalla
        cout << "Semilla = " <<  this->seed << " || Generación " << this->generationNumber << "|| Coste = " << this->getPopulation().getBestIndividual().getCost()
             << " || Mejor coste = " << this->getBestIndividual().getCost()  << " ||  Tiempo empleado = " << time
             << " || mejor solución = ";
        this->getBestIndividual().print();
        cout << endl;

        // Generamos un registro cada 10 generaciones
        if(i%10 == 0){
            outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
                    <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;
        }
        // Incrementamos en uno el número de generaciones de la población del algoritmo.
        this->generationNumber++;
    }

    outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
            <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;

    outfile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Algoritmo evolutivo que no utiliza algoritmo de optimización local para generar la población inicial optimizada tras cada generación.
void GeneticAlgorithm::fastEvolution(int generationIterations){

    int randomNum; // Número aleatorio para la mutación
    int mutationNumber; // Número límite según la probabilidad de mutación
    double time; // Variable para medir el tiempo

    unsigned t0, t1; // Valores donde se va almacenar temporalmente los valores del tiempo

    // Generamos el límite para el número aleatorio. Cuidamos no hacer la operación módulo 0
    if(this->mutationProbability != 0)
        mutationNumber= 1 / this->mutationProbability;
    else
        mutationNumber = 1;

    // Creamos un fichero para almacenar los resultados.
    ofstream outfile ("logs/fastEvolution/log_"+ this->data.getFilename() +".txt");

    for(int i = 0; i < generationIterations; ++i){

        t0=clock();

        // Se calcula un número aleatorio comprendido entre 0 y el límite.
        randomNum = rand()%mutationNumber;

        // Se genera la selección de los padres y se actualiza la población
        // Pasamos valor false porque la generación no es Baldwiniana
        this->generateParentsGeneration();

        // Se actualiza la población con los hijos resultados de la combinación entre padres (2 padres = 2 hijos).
        this->generateChildrenGeneration();

        // Si por ejemplo el número aleatorio es 2, realizamos la mutación del individuo
        if(randomNum == 2){
            this->mutate( rand() % this->population.getSize() );
        }

        // Se comprueba si se ha mejorado la solución actual, en tal caso se actualiza
        this->checkBestIndividual();

        t1 = clock();
        time = (double(t1-t0)/CLOCKS_PER_SEC);

        // Se muestra la información resultante por pantalla
        cout << "Semilla = " <<  this->seed << " || Generación " << this->generationNumber << "|| Coste = " << this->getPopulation().getBestIndividual().getCost()
             << " || Mejor coste = " << this->getBestIndividual().getCost()  << " ||  Tiempo empleado = " << time
             << " || mejor solución = ";
        this->getBestIndividual().print();
        cout << endl;

        // Generamos un registro cada 10 generaciones
        if(i%10 == 0){
            outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
                    <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;
        }

        // Incrementamos en uno el número de generaciones de la población del algoritmo.
        this->generationNumber++;
    }

    outfile << this->generationNumber << "\t" << this->getPopulation().getBestIndividual().getCost()
            <<"\t" << this->getBestIndividual().getCost()  << "\t" << time << endl;

    outfile.close();
}



