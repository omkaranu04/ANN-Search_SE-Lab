#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include <vector>
#include <math.h>
using namespace std;

// DataVector class to handle all sorts of vector related operations and tasks
// The DataVector class implements the mathematical notion of a vector
class DataVector
{
    vector<double> v;
    int dimension_;

public:
    DataVector(int dimension = 0);                // Constructor
    DataVector(double data[], int dimension = 0); // Constructor
    DataVector(vector<double> &data);             // Constructor
    ~DataVector();                                // Destructor
    DataVector(const DataVector &other);          // Copy Constructor
    void setDimension(int dimension = 0);         // Function to set Dimension of Vector

    DataVector &operator=(const DataVector &other); // Assignment Operator
    DataVector operator+(const DataVector &other);  // Addition Operator
    DataVector operator-(const DataVector &other);  // Subtraction Operator
    bool operator<(const DataVector &other) const;  //< operator overloading
    bool operator==(const DataVector &other) const; //== operator overloading
    double operator*(const DataVector &other);      // Dot Product Operator

    double norm();                            // Function to Calculate norm of the vector
    double distance(const DataVector &other); // Function to Calculate distance between two Vectors

    int getDimension() const;                    // Function to get Dimension of the Vector
    double getitem(int i) const;                 // Function to get the i-th parameter of the Vector
    void setitem(int index, double value);       // Function to set the value of i-th parameter of the Vector
    int size() const;                            // to return the dimension of the vector
    bool compare(const DataVector &other) const; // to compare two datavectors for if they are equal or not
};

#endif