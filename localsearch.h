#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "data.h"
#include "individual.h"

class LocalSearch
{
public:

   LocalSearch();

   Individual LocalSearch_1(Data &data,Individual &firstIndividual, int numIterations);
};

#endif // LOCALSEARCH_H

