#include <bits/stdc++.h>
#include "DataVector.h"
#include "VectorDataset.h"
#include "TreeIndex.h"
#include "KDTreeIndex.h"
#include "RPTreeIndex.h"
using namespace std;

int main(int argc, char const *argv[])
{
    VectorDataset train, test;
    // Reads the .csv files given into to VectorDataset separately as train and test
    cout << "Reading Data Started" << endl;
    cout << ". . . . ." << endl;

    train.readDataSet("fmnist-train.csv");
    test.readDataSet("fmnist-test.csv");

    cout << ". . . . ." << endl;
    cout << "Reading Data Ended" << endl;
    cout << "Train Size : "
         << " " << train.size() << endl;
    cout << "Test Size : "
         << " " << test.size() << endl;

    int q;
    cout << "Enter 1 for KDTree and 2 for RPTree : ";
    cin >> q;

    if (q == 1)
    {

        /*---------- KD TREE ----------*/
        /*-----------------------------*/
        KDTreeIndex &kdTree = KDTreeIndex::GetInstance();
        cout << "Building KD Tree Started" << endl;
        cout << ". . . . ." << endl;
        kdTree.dataset = train.data;
        kdTree.MakeTree();
        cout << ". . . . ." << endl;
        cout << "Building KD Tree Ended" << endl;

        // Taking the input for k
        int k;
        cout << "Enter k : ";
        cin >> k;

        // For finding k-nearest neighbours
        // cout << "FINDING K NEAREST" << endl;
        // DataVector query = test.getDataVector(67);
        // vector<DataVector> k_near = kdTree.Search(query, k);
        // cout << "FOUND K NEAREST" << endl;

        for (int i = 0; i < 100; i++)
        {
            DataVector query = test.getDataVector(i);
            vector<DataVector> k_near = kdTree.Search(query, k);
            cout << "Completed : " << i + 1 << endl;
        }

        /*-----------------------------*/
        /*--------- KD TREE ---------*/
    }

    else if (q == 2)
    {
        /*--------- RP TREE ---------*/
        /*-----------------------------*/
        RPTreeIndex &rpTree = RPTreeIndex::GetInstance();
        cout << "Building RP Tree Started" << endl;
        cout << ". . . . ." << endl;
        rpTree.dataset = train.data;
        rpTree.MakeTree();
        cout << ". . . . ." << endl;
        cout << "Building RP Tree Ended" << endl;

        // Taking the input for k
        int k;
        cout << "Enter k : ";
        cin >> k;

        // For finding k-nearest neighbours
        // cout << "FINDING K NEAREST" << endl;
        // DataVector query = test.getDataVector(67);
        // vector<DataVector> k_near_2 = rpTree.Search(query, k);
        // cout << "FOUND K NEAREST" << endl;

        for (int i = 0; i < 100; i++)
        {
            DataVector query = test.getDataVector(i);
            vector<DataVector> k_near = rpTree.Search(query, k);
            cout << "Completed : " << i + 1 << endl;
        }

        /*-----------------------------*/
        /*--------- RP TREE ---------*/
    }

    else
    {
        return 0;
    }

    return 0;
}