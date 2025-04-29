#include "DataVector.h"

// Constructor when only dimension of the vector is known
DataVector::DataVector(int dimension)
{
    this->setDimension(dimension);
}

// Constructor when the data and the dimension of the vector is known
DataVector::DataVector(double data[], int dimension)
{
    this->setDimension(dimension);
    v.assign(data, data + dimension);
}

// Constructor when the data is known and is in the form of a C++ vector
DataVector::DataVector(vector<double> &data)
{
    v = data;
    dimension_ = v.size();
}

// Destructor
DataVector::~DataVector()
{
}

// Copy Constructor
DataVector::DataVector(const DataVector &other)
{
    v = other.v;
    dimension_ = other.dimension_;
}

// A function that sets the dimension of the vector and initialises it with 0.0
void DataVector::setDimension(int dimension)
{
    dimension_ = dimension;
    v.resize(dimension_, 0.0);
}

// Assignment operator being overloaded according to the class
DataVector &DataVector::operator=(const DataVector &other)
{
    if (this != &other)
    {
        dimension_ = other.dimension_;
        v = other.v;
    }
    return *this;
}

// Addition operator being overloaded for the class to perform vector addition
DataVector DataVector::operator+(const DataVector &other)
{
    DataVector add(dimension_);
    for (size_t i = 0; i < dimension_; i++)
    {
        add.v[i] = v[i] + other.v[i];
    }
    return add;
}

// Subtraction operator being overloaded for the class to perform vector subtraction
DataVector DataVector::operator-(const DataVector &other)
{
    DataVector sub(dimension_);
    for (size_t i = 0; i < dimension_; i++)
    {
        sub.v[i] = v[i] - other.v[i];
    }
    return sub;
}

// Multiplication operator being overloaded for the class to perform vector dot product
double DataVector::operator*(const DataVector &other)
{
    double dot = 0.0;
    for (size_t i = 0; i < dimension_; i++)
    {
        dot += v[i] * other.v[i];
    }
    return dot;
}

// Member function to calculate the norm of the vector
double DataVector::norm()
{
    double sq_sum = (*this) * (*this);
    return sqrt(sq_sum);
}

// Member function to find the distance between two vectors using norm method implemented above
double DataVector::distance(const DataVector &other)
{
    DataVector diff = *this - other;
    double distance_ = diff.norm();
    return distance_;
}

// Function that returns the dimension of the vector on call
int DataVector::getDimension()
{
    return dimension_;
}

// Function that returns the value at a given index i in the vector
double DataVector::getitem(int i)
{
    return v[i];
}

// Function that sets the value of the given index in the vector to a given value
void DataVector::setitem(int index, double value)
{
    v[index] = value;
}