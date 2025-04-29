#include "RPTreeIndex.h"
#include <bits/stdc++.h>
using namespace std;

// Class constructor
RPTreeIndex::RPTreeIndex() : root(nullptr) {}

// class destructor
RPTreeIndex::~RPTreeIndex()
{
    DeleteTree(root);
}

// function that selects the random dimension to split the dataset, uses uniform distribution
int RPTreeIndex::selectRandomDimension(int dimensions)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, dimensions - 1);
    return dis(gen);
}

// calculate the radius if the node based in the maximum distance between any two points in the dataset
double RPTreeIndex::calculateRadius(vector<DataVector> &dataset)
{
    double radius = 0.0;
    for (auto &vec : dataset)
    {
        for (auto &other : dataset)
        {
            double dist = distance(vec, other);
            if (dist > radius)
                radius = dist;
        }
    }
    return radius;
}

// recursively delete the tree starting from given node
void RPTreeIndex::DeleteTree(RPTreeNode *node)
{
    if (node == nullptr)
        return;

    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

// delete the whole tree from the root itself
void RPTreeIndex::ClearTree()
{
    DeleteTree(root);
    root = nullptr;
}

// getinstance() method for singleton instance
RPTreeIndex &RPTreeIndex::GetInstance()
{
    static RPTreeIndex instance;
    return instance;
}

// function to add a data point in the tree
void RPTreeIndex::AddData(const DataVector &data)
{
    ClearTree();
    dataset.push_back(data);
    MakeTree();
}

// function to delete a datapoint in the tree
void RPTreeIndex::RemoveData(const DataVector &data)
{
    ClearTree();
    auto it = find(dataset.begin(), dataset.end(), data);
    if (it != dataset.end())
        dataset.erase(it);
    MakeTree();
}

// function to build the tree
void RPTreeIndex::MakeTree()
{
    if (root != nullptr)
        return;
    root = buildRPTree(dataset, 0, 20);
}

// function to choose the splitting dimension
int RPTreeIndex::ChooseRule(const vector<DataVector> &dataset)
{
    return selectRandomDimension(dataset[0].size());
}

// recursive function to build the tree from the root level
RPTreeIndex::RPTreeNode *RPTreeIndex::buildRPTree(vector<DataVector> &dataset, int depth, int maxDepth)
{
    cout << dataset.size() << " ";
    if (dataset.size() <= 1 || depth >= maxDepth)
    {
        if (dataset.size() == 1)
        {
            return new RPTreeNode(dataset[0]);
        }
        else
        {
            return nullptr;
        }
    }

    int dimensions = dataset[0].size();
    if (depth >= dimensions)
    {
        return new RPTreeNode(dataset[0]);
    }

    int splitDimension = ChooseRule(dataset); // Choose split dimension using the ChooseRule function

    sort(dataset.begin(), dataset.end(), [=](const DataVector &a, const DataVector &b)
         { return a.getitem(splitDimension) < b.getitem(splitDimension); });

    RPTreeNode *node = new RPTreeNode(dataset[dataset.size() / 2]);
    node->splitDimension = splitDimension;
    node->splitValue = dataset[dataset.size() / 2].getitem(splitDimension);

    vector<DataVector> left_(dataset.begin(), dataset.begin() + dataset.size() / 2);
    vector<DataVector> right_(dataset.begin() + dataset.size() / 2 + 1, dataset.end());

    node->left = buildRPTree(left_, depth + 1, maxDepth);
    node->right = buildRPTree(right_, depth + 1, maxDepth);
    node->radius = calculateRadius(dataset);

    return node;
}

// function to find the distance between two data points
double RPTreeIndex::distance(DataVector &a, DataVector &b)
{
    return a.distance(b);
}

// returns the found k nearest neighbours of the query data
vector<DataVector> RPTreeIndex::Search(DataVector &query, int k)
{
    std::vector<DataVector> result;
    nearestNeighborSearch(root, query, k, result);
    return result;
}

// recursive function to perform the nearest neighbour search in the rp tree
void RPTreeIndex::nearestNeighborSearch(RPTreeNode *node, DataVector &query, int k, vector<DataVector> &result)
{
    if (node == nullptr)
        return;

    double dist = distance(node->data, query);
    if (result.size() < k || dist < distance(result[result.size() - 1], query))
    {
        if (result.size() == k)
            result.pop_back();
        result.push_back(node->data);
        std::sort(result.begin(), result.end(), [&](DataVector &a, DataVector &b)
                  { return distance(a, query) < distance(b, query); });
    }

    double planeDist = std::abs(query.getitem(node->splitDimension) - node->splitValue);
    if (dist < planeDist + node->radius)
    {
        if (query.getitem(node->splitDimension) < node->splitValue)
        {
            nearestNeighborSearch(node->left, query, k, result);
            if (node->splitValue - planeDist <= query.getitem(node->splitDimension))
                nearestNeighborSearch(node->right, query, k, result);
        }
        else
        {
            nearestNeighborSearch(node->right, query, k, result);
            if (node->splitValue + planeDist >= query.getitem(node->splitDimension))
                nearestNeighborSearch(node->left, query, k, result);
        }
    }
}