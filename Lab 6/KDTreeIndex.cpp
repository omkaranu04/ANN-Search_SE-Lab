#include "KDTreeIndex.h"
#include <bits/stdc++.h>
using namespace std;
/*
The details of every function has been mentioned above it
Also in the .h file the details of function has been commented
*/

// Class Constructor
KDTreeIndex::KDTreeIndex() : root(nullptr) {}

// function to recursively delete the tree
void KDTreeIndex::deleteTree(KDTreeNode *node)
{
    if (node == nullptr)
        return;

    // Recursively delete the left and right subtrees
    deleteTree(node->left);
    deleteTree(node->right);

    // Delete the current node
    delete node;
}

// Implement deletion of the KD tree
KDTreeIndex::~KDTreeIndex()
{
    // Call the helper function to delete the KD tree
    deleteTree(root);
}

// GetInstance to maintain singletoness of the class
KDTreeIndex &KDTreeIndex::GetInstance()
{
    static KDTreeIndex instance;
    return instance;
}

// Function to Add a datapoint in the tree
void KDTreeIndex::AddData(const DataVector &data)
{
    if (root == nullptr)
    {
        root = new KDTreeNode(data);
    }
    else
    {
        deleteTree(root);
        dataset.push_back(data);
        MakeTree();
    }
}

// Function to remove a datapoint from the tree
void KDTreeIndex::RemoveData(const DataVector &data)
{
    for (auto it = dataset.begin(); it != dataset.end(); ++it)
    {
        if (*it == data)
        {
            dataset.erase(it);
            deleteTree(root);
            MakeTree();
            break;
        }
    }
}

// function to find the node with minimum value in the tree by recursively travelling the left subtree
KDTreeNode *KDTreeIndex::findMin(KDTreeNode *node, int depth)
{
    if (node == nullptr)
        return nullptr;

    int k = node->data.size();
    int axis = depth % k;

    if (node->left == nullptr)
        return node;

    return findMin(node->left, depth + 1);
}

// function to build the tree
void KDTreeIndex::MakeTree()
{
    if (root != nullptr)
        return;
    root = buildTree(dataset, 0);
}

// chooseRule function
int KDTreeIndex::chooseRule(int depth, int k)
{
    return depth % k;
}

// function to recursively build the tree by sorting the dataset along the current axis and then choosing the median value as the root
KDTreeNode *KDTreeIndex::buildTree(vector<DataVector> &dataset, int depth)
{
    if (dataset.empty())
        return nullptr;

    int axis = chooseRule(depth, dataset[0].size());

    auto comp = [axis](const DataVector &a, const DataVector &b)
    {
        return a.getitem(axis) < b.getitem(axis);
    };

    sort(dataset.begin(), dataset.end(), comp);
    int median = dataset.size() / 2;

    KDTreeNode *node = new KDTreeNode(dataset[median]);
    vector<DataVector> left_(dataset.begin(), dataset.begin() + median);
    vector<DataVector> right_(dataset.begin() + median + 1, dataset.end());
    // cout << "left ";
    node->left = buildTree(left_, depth + 1);
    // cout << "right ";
    node->right = buildTree(right_, depth + 1);
    return node;
}

// function to calculate the distance between two points
double KDTreeIndex::distance(DataVector &a, DataVector &b)
{
    return a.distance(b);
}

// functuion to find the k nearest neighbour in the tree, it recursively traverses the tree updating the priority queue
void KDTreeIndex::nearestNeighborSearch(KDTreeNode *node, DataVector &query, int k, priority_queue<pair<double, DataVector>> &pq)
{
    if (node == nullptr)
    {
        return;
    }

    double dist = query.distance(node->data);
    pq.push({dist, node->data});

    if (pq.size() > k)
        pq.pop();

    int axis = pq.size() % query.size();

    KDTreeNode *nearChild = (query.getitem(axis) < node->data.getitem(axis)) ? node->left : node->right;
    KDTreeNode *farChild = (query.getitem(axis) < node->data.getitem(axis)) ? node->right : node->left;

    // cout << "k_near ";
    nearestNeighborSearch(nearChild, query, k, pq);

    if (!pq.empty())
    {
        double longest = pq.top().first;
        double plane = abs(node->data.getitem(axis) - query.getitem(axis));
        if (plane < longest)
            nearestNeighborSearch(farChild, query, k, pq);
    }
}

// function initiates the k-nearest neighbour search, collects the results from the priority queue and returns them as a vector
vector<DataVector> KDTreeIndex::Search(DataVector &query, int k)
{
    priority_queue<pair<double, DataVector>> pq;
    nearestNeighborSearch(root, query, k, pq);

    vector<DataVector> nearestNeighbors;
    while (!pq.empty())
    {
        nearestNeighbors.push_back(pq.top().second);
        pq.pop();
    }

    return nearestNeighbors;
}