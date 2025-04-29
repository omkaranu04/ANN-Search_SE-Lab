#ifndef KDTREEINDEX_H
#define KDTREEINDEX_H

#include "TreeIndex.h"

/*
The KD Tree divides the dataset at each level bases on a chosen dimension and a splitting value
At first the simension to be split is chosen and the splitting value is selected to split the data in the next level
Here median is used as the splitting value and the data points along the given dimension if smaller than median go to the left subtree and the rest goes to the right subtree
These two aspects of selecting the dimension and splitting according to the median forms the basis of building the KD Tree
Next part comes of finding the k nearest neighbours
The kd tree traverses along recursively starting at the root, at each node it compares the query datapoint with the splitting value along the chosen dimension
based on the comparison it decides which subtree to traverse along, a priority queue is maintained to keep the track of all the points added to the k-nearest neighbours list
*/

class KDTreeNode // Node Structure for the KD Tree
{
public:
    DataVector data;
    KDTreeNode *left;
    KDTreeNode *right;

    KDTreeNode(const DataVector &data) : data(data), left(nullptr), right(nullptr) {} // Constructor
};

class KDTreeIndex : public TreeIndex // KD Tree Index Class, inheriting from the TreeINDex
{
public:
    static KDTreeIndex &GetInstance();                                                                                    // Singleton pattern to get an instance of the KDTreeIndex
    void AddData(const DataVector &data) override;                                                                        // Add a data point to the KD Tree
    void RemoveData(const DataVector &data) override;                                                                     // Remove a data point from the KD Tree
    void MakeTree() override;                                                                                             // Function to build the KD Tree
    vector<DataVector> Search(DataVector &query, int k) override;                                                         // Search for the k-nearest neighbours of a query point in the KD Tree
    vector<DataVector> dataset;                                                                                           // Dataset of points for the KD Tree
    void nearestNeighborSearch(KDTreeNode *node, DataVector &query, int k, priority_queue<pair<double, DataVector>> &pq); // Recursive function for the k-nearest neighbour search for a query point in the KD Tree
    KDTreeNode *root;
    int chooseRule(int depth, int k); // The root node of the KD Tree

private:
    KDTreeIndex();                                                 // Constructor of the KDTreeIndex Class
    ~KDTreeIndex();                                                // Destructor of the KDTreeIndex Class
    void deleteTree(KDTreeNode *node);                             // Recursive function to delete the entire KD Tree
    KDTreeNode *buildTree(vector<DataVector> &dataset, int depth); // Recursive function to build the whole KD Tree
    double distance(DataVector &a, DataVector &b);                 // Calculate the distance between two datapoints
    KDTreeNode *findMin(KDTreeNode *node, int depth);              // Helper function to find the minimum value node in a subtree
};

#endif