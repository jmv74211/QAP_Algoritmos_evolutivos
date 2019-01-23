#include <iostream>
#include "data.h"
#include "individual.h"

#include <vector>

using namespace std;

int main(){

    const int seed = 2;

    Data data = Data("bur26a.dat");

    Individual individual = Individual(data, seed);
    Individual individual2 = Individual(data, 5);

    return 0;
}
