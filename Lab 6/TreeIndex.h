#ifndef TREEINDEX_H
#define TREEINDEX_H

#include "DataVector.h"
#include "VectorDataset.h"
#include <bits/stdc++.h>
using namespace std;

/*
Two tree indices namely RPTReeINdex and KDTreeINdex have been derived from the given base class
This a a singleton class
*/
// This is the base class for the tree-based index structures
class TreeIndex
{
protected:
    TreeIndex() {}          // Constructor
    virtual ~TreeIndex() {} // Destructor

public:
    static TreeIndex &GetInstance();                                 // function to get a reference to the singleton instance of the treeindex
    virtual void AddData(const DataVector &data) = 0;                // add a datapoint to the tree
    virtual void RemoveData(const DataVector &data) = 0;             // remove a datapoint from the tree
    virtual void MakeTree() = 0;                                     // build a tree structure based on added data
    virtual vector<DataVector> Search(DataVector &query, int k) = 0; // search for k nearest neighbour of the given query
    vector<DataVector> dataset;                                      // dataset to store the data points
};

#endif