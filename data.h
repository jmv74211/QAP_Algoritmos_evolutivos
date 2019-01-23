#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <vector>

using namespace std;

class Data{

    private:

        vector<vector<unsigned int> > factorys;

        vector<vector<unsigned int> > distances;

        unsigned int size;

    public:

        Data();

        unsigned int getSize();

        unsigned int getMatrixFactorys();

        unsigned int getMatrixDistances();

        int getFactory(unsigned i, unsigned j);

        int getDistance(unsigned i, unsigned j);

        void readFile(const char * filename);

};

#endif
