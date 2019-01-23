#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <vector>

using namespace std;

class Data{

    private:

        vector<vector<int> > factorys;

        vector<vector<int> > distances;

        int size;

    public:

        Data();

        Data(const char * filename);

        int getSize();

        vector<vector<int> > getMatrixFactorys();

        vector<vector<int> > getMatrixDistances();

        int getFactory(unsigned i, unsigned j);

        int getDistance(unsigned i, unsigned j);

        void readFile(const char * filename);

        void printFactorys();

        void printDistances();

};

#endif
