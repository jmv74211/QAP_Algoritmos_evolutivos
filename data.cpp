#include "data.h"
#include <iostream>
#include <stdio.h>


Data::Data(){
    this->size = 0;
}

Data::Data(const char * filename){

    this->readFile(filename);
}

vector<vector<int> > Data::getMatrixFactorys(){
     return this->factorys;
}

vector<vector<int> > Data::getMatrixDistances(){
     return this->distances;
}


int Data::getSize(){
    return this->size;
}

int Data::getDistance(unsigned i, unsigned j){
    return this->distances[i][j];
}

int Data::getFactory(unsigned i, unsigned j){
    return this->factorys[i][j];
}

void Data::readFile(const char * filename){

    ifstream file;
    file.open(filename);

    int dataSize = 0;

    file >> dataSize ;

    if (file.is_open()) {
        cout << "11111" << endl;
        file >> dataSize;
        this->distances = vector<vector<int> >(dataSize, vector<int>(dataSize));
        this->factorys = vector<vector<int> >(dataSize, vector<int>(dataSize));

        for(unsigned i = 0; i < this->factorys.size(); ++i){
            for(unsigned j = 0; j < this->factorys.size(); ++j){
                file >> this->factorys[i][j];
            }
        }
        for(unsigned i = 0; i < this->distances.size(); ++i){
            for(unsigned j=0; j < this->distances.size() ; ++j){
                file >> this->distances[i][j];
            }
        }
      }
      else {
        perror("Fichero no encontrado");
      }

        this->size = dataSize;
        cout << dataSize << endl;
        file.close();
}


