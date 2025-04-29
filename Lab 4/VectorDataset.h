#include "DataVector.h"
#include <string>
#include <fstream>
#include <sstream>

// VectorDataset class to handle all related functionalities
class VectorDataset
{
    vector<DataVector> data;
    int n;

public:
    // Constructor
    VectorDataset(int n = 0) : n(n)
    {
    }

    // Destructor
    ~VectorDataset()
    {
    }

    // Member function to add a Datavector to the VectorDataset
    void addDataVector(DataVector vec_tor)
    {
        n++;
        data.push_back(vec_tor);
    }

    // Member function to return the whole VectorDataset
    vector<DataVector> get()
    {
        return data;
    }

    // Member function to get the vector member of the VectorDataset of the given index
    DataVector getDataVector(int index)
    {
        return data[index];
    }

    // Member function to return the size of the VectorDataset
    int size()
    {
        return n;
    }

    // Member function to read the VectorDataset from a given .csv file and store it in a VectorDataset
    void readDataSet(string path)
    {
        ifstream file;
        file.open(path);

        n = 0;
        string line, field;

        while (getline(file, line))
        {
            n++;
            vector<double> curr;
            istringstream iss(line);

            while (getline(iss, field, ','))
            {
                curr.push_back(stod(field));
            }
            data.push_back(DataVector(curr));
        }
        file.close();
    }
};