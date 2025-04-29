#ifndef RPTREEINDEX_H
#define RPTREEINDEX_H

#include "TreeIndex.h"

/*
The Rp tree splits the data at each internal node based on a randomly chosen dimension, which is done using ChooseRule dimension
the split dimension uses the uniform distribution based on the number of dimension to ensure randomness in splitting and prevent bias towards any particular dimension
for searching the k nearest neighbours
the tree is traversed recursively, at each internal node the splitting dimension is considered to decide which subtree to explore
the distance between the current node's data point and the query is calculated, if it is shorter than the farthest neighbour so far, the result vector is updated
*/

class RPTreeIndex : public TreeIndex // RPTreeINdex class inheriting from the TreeIndex
{
public:
    struct RPTreeNode // rptreenode struct to represent the nodes in rptree
    {
        DataVector data;
        RPTreeNode *left;
        RPTreeNode *right;
        int splitDimension; // dimension used for splitting
        double splitValue;  // value used for splitting
        double radius;      // radius of the node
        RPTreeNode(const DataVector &data) : data(data), left(nullptr), right(nullptr), splitDimension(-1), splitValue(0), radius(0) {}
    };
    static RPTreeIndex &GetInstance();                                                                  // to get a singleton instance of the rptreeindex class
    void AddData(const DataVector &data) override;                                                      // function to add data to the tree
    void RemoveData(const DataVector &data) override;                                                   // function to remove data from the tree
    void MakeTree() override;                                                                           // function to make the tree
    vector<DataVector> Search(DataVector &query, int k) override;                                       // function to search for k nearest neighbours
    vector<DataVector> dataset;                                                                         // dataset of points
    RPTreeNode *root;                                                                                   // root of the tree
    void nearestNeighborSearch(RPTreeNode *node, DataVector &query, int k, vector<DataVector> &result); // function to recursively search for the k nearest neighbours of the query point

private:
    RPTreeIndex();                                                                 // constructor of the class
    ~RPTreeIndex();                                                                // destructor of the class
    void DeleteTree(RPTreeNode *node);                                             // function to delete the tree recursively
    void ClearTree();                                                              // function to clear the tree, deleting all nodes // cleartree in turn calls delete tree
    int ChooseRule(const vector<DataVector> &dataset);                             // choosing a random dimension for splitting
    RPTreeNode *buildRPTree(vector<DataVector> &dataset, int depth, int maxDepth); // recursively build the rp tree
    int selectRandomDimension(int dimensions);                                     // select a random dimension for splitting
    double calculateRadius(vector<DataVector> &dataset);                           // calculate the radius of the node in the tree
    double distance(DataVector &a, DataVector &b);                                 // function to calculate the distance between two points
};

#endif