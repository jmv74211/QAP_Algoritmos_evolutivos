#include <iostream>
#include <cstdlib>
#include <ctime>


#include "data.h"
#include "geneticalgorithm.h"

using namespace std;

int main( int argc, char* argv[] ){

    /*const int populationSeed = 2;
    const int geneticAlgorithmSeed = 2;
    const int individualsNum = 60;
    const int generationNum = 60000;
    const int numIterations = 60000;*/

    //Data data = Data("chr22a.dat");

    //Data data = Data("tai256c.dat");

    char *filename = argv[1];
    int generationNum = atoi(argv[2]);
    int populationSeed = atoi(argv[3]);
    string option = argv[4];
    string subdirectory;
    int geneticAlgorithmSeed = populationSeed;
    const int individualsNum = 60;
    unsigned t0, t1;
    double time;

    t0=clock();

    Data data = Data(filename);



    Population population = Population(populationSeed, individualsNum, data);

    population.sortPopulation();

    GeneticAlgorithm geneticAlgorithm = GeneticAlgorithm(data,population,geneticAlgorithmSeed);

    if(option == "lamarck"){
        cout << "Ejecutando evolución de lamarck" << endl;
        subdirectory="lamarckEvolution";
        geneticAlgorithm.lamarckEvolution(generationNum);
    }
    else if((option == "baldwin")){
        cout << "Ejecutando evolución de baldwin " << endl;
        subdirectory="baldwinEvolution";
        geneticAlgorithm.baldwinEvolution(generationNum);
    }
    else{
        cout << "Ejecutando evolución genética sin optimización local" << endl;
        subdirectory="fastEvolution";
        geneticAlgorithm.fastEvolution(generationNum);
    }


    string outName = "logs/" + subdirectory + "/log_BEST_RESULT_"+ to_string(generationNum) + "_generations_" + (string) filename + ".txt";

    ofstream outfile (outName);

    cout << endl << endl << endl << endl << endl;
    cout << " --------------------------------------------------------------" << endl;

    cout << "La mejor solución encontrada tiene coste = " << geneticAlgorithm.getBestIndividual().getCost()
         << " y pertenece al individuo --> ";

    geneticAlgorithm.getBestIndividual().print();
    cout << endl;

    cout << " --------------------------------------------------------------" << endl;
    cout << endl << endl << endl << endl << endl;


    outfile << "La mejor solución encontrada tiene coste = " << geneticAlgorithm.getBestIndividual().getCost()
            << " y pertenece al individuo --> ";


    int limit =  geneticAlgorithm.getPopulation().getIndividual(0).getSize();

    outfile << "[ ";
    for(int j = 0 ; j < limit; ++j){
        outfile << geneticAlgorithm.getBestIndividual().getVectorSolutions().at(j)  << " ";
    }
     outfile << " ]" << endl;

    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC);


    outfile  << endl << endl <<  "La ejecución del programa ha tardado: " << time << "s" <<endl;

    outfile.close();

    cout  <<  endl << endl <<  "La ejecución del programa ha tardado: " << time << "s" <<endl <<endl <<endl;



























    /*
     * TEST PARA CALCULAR EL COSTE DE UN INDIVIDUO
    vector<int> individual1;
    individual1.push_back(20);individual1.push_back(6);individual1.push_back(3);individual1.push_back(14);individual1.push_back(19);
    individual1.push_back(1);individual1.push_back(10);individual1.push_back(13);individual1.push_back(9);individual1.push_back(12);
    individual1.push_back(18);individual1.push_back(7);individual1.push_back(21);individual1.push_back(0);individual1.push_back(5);
    individual1.push_back(15);individual1.push_back(11);individual1.push_back(8);individual1.push_back(2);individual1.push_back(17);
    individual1.push_back(16);individual1.push_back(4);

    Individual individual = Individual(data,2,individual1);

    cout << individual.getCost() << endl;


    */



    /*
     *  PRUEBA DE GENERACIÓN PADRE, HIJO Y MUTACIÓN
    cout << endl << endl << endl;

    geneticAlgorithm.newLamarckGeneration(numIterations);



    int initalCost = population.calculatePoblationCost();
    int optimizedCost = geneticAlgorithm.getPopulation().calculatePoblationCost();

    geneticAlgorithm.generateParentsGeneration();

    geneticAlgorithm.getPopulation().print();

    int parentsCost = geneticAlgorithm.getPopulation().calculatePoblationCost();


    geneticAlgorithm.generateChildrenGeneration();

    int childrenCost = geneticAlgorithm.getPopulation().calculatePoblationCost();

    geneticAlgorithm.getPopulation().print();

    cout << "Coste inicial = " << initalCost  << endl;
    cout << "Coste optimizado = " << optimizedCost << endl;
    cout << "Coste padres = " << parentsCost << endl;
    cout << "Coste hijos = " << childrenCost << endl;

    cout << "El mejor individuo encontrado es " <<endl;
    geneticAlgorithm.getBestIndividual().print();
    cout << "Coste = " << geneticAlgorithm.getBestIndividual().getCost() << endl;

    cout << endl << endl << endl << endl;

    cout << "Mutación" <<endl;
    geneticAlgorithm.getPopulation().getIndividual(59).print();
    int coste1 = geneticAlgorithm.getPopulation().getIndividual(59).getCost();
    geneticAlgorithm.mutate(59);
    geneticAlgorithm.getPopulation().getIndividual(59).print();
    int coste2 = geneticAlgorithm.getPopulation().getIndividual(59).getCost();
    cout << "Coste 1 = " << coste1 <<endl;
    cout << "Coste 2 = " << coste2 <<endl;

         FIN PRUEBA DE GENERACIÓN PADRE, HIJO Y MUTACIÓN
    */














   /*for( int i = 0; i < geneticAlgorithm.getPopulation().getSize(); ++i){
       cout << geneticAlgorithm.getPopulation().getIndividual(i).getCost() << endl;
   }
   geneticAlgorithm.generateParentsGeneration();

   cout << endl << endl << endl;

   cout << "Generación de padres" << endl;
   geneticAlgorithm.sort();
   geneticAlgorithm.getPopulation().print();
   int cost = geneticAlgorithm.getPopulation().calculatePoblationCost();

   geneticAlgorithm.generateChildrenGeneration();

   cout << "Generación de hijos" << endl;
   geneticAlgorithm.sort();
   geneticAlgorithm.getPopulation().print();

   cout << endl;
   cout << "Coste población padre = " << cost <<  endl;
   cout << "Coste población hija = " << geneticAlgorithm.getPopulation().calculatePoblationCost() <<  endl;

   geneticAlgorithm.mutate(0);
   cout << endl << endl;
   geneticAlgorithm.getPopulation().print();

    */














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
