#include "VectorDataset.h"
#include <bits/stdc++.h>
using namespace std;

/*
THE K-NEAREST NEIGHBOUR ALGORITHM
The function takes a VectorDataset, a sample vector and a integer value k as input
The function calculates the k - nearest neighbours of the sample vector within the given dataset
The algorithm uses the Heap-Sort implementation using the priority queue using the C++ STL Library to return a VectorDataset of k nearest neighbour vectors of the sample vector

The main function in this, first of all reads the two provided datasets namely fmnist-train and fmnist-test in two VectorDataset class
It asks the user to input the value of k on the basis of which the k - nearest neighbours of the sample vector are found out
The main function prints the total time required to find the k - nearest neighbours of the "vectors in test dataset" from the "vectors in train dataset" and prints it on the screen in milliseconds
"As per my interpretation of the question the k - nearest neighbours of "vectors from test dataset" from "vectors of train dataset" is to be found"
*/

// The nearestneighbour function that returns a vectorDataset containing the k - nearest Datavectors of the sample vector from the given VectorDataset
VectorDataset nearestneighbour(VectorDataset &data, DataVector &sample, int k)
{
    VectorDataset k_nearest_neighbours;
    if (data.size() == 0)
        cout << "Dataset is empty" << endl;
    else
    {
        // Heap Sort Implementation using priority queue of the STL
        priority_queue<pair<double, int>> max_heap;
        for (int i = 0; i < data.size(); i++)
        {
            double distance = sample.distance(data.getDataVector(i));
            {
                if (max_heap.size() < k || distance < max_heap.top().first)
                {
                    max_heap.push(make_pair(distance, i));
                    if (max_heap.size() > k)
                        max_heap.pop();
                }
            }
        }

        while (!max_heap.empty())
        {
            k_nearest_neighbours.addDataVector(data.getDataVector(max_heap.top().second));
            max_heap.pop();
        }

        reverse(k_nearest_neighbours.get().begin(), k_nearest_neighbours.get().end());
    }
    return k_nearest_neighbours;
}

int main(int argc, char const *argv[])
{
    VectorDataset train, test;
    // Reads the .csv files given into to VectorDataset separately
    cout << "Reading Data Started" << endl;
    cout << ". . . . ." << endl;

    train.readDataSet("fmnist-train.csv");
    test.readDataSet("fmnist-test.csv");

    cout << ". . . . ." << endl;
    cout << "Reading Data Ended" << endl;

    // Prompts the user to input the value of k for the k - nearest vectors search algorithm
    int k;
    cout << "Enter the Value of k : ";
    cin >> k;

    // The clock for time reporting starts
    auto start_time = chrono::high_resolution_clock::now();

    cout << "Search Started with k = " << k << endl;

    VectorDataset k_set;
    int i = 1;

    // Traverses over individual vectors from the test dataset
    for (auto vec : test.get())
    {
        // Finds the k-nearest neighbours from the train dataset of the provided sample DataVector
        k_set = nearestneighbour(train, vec, k);
        if (k_set.size() != k)
        {
            cout << "Error in " << i << endl;
            break;
        }
        cout << "Complete : " << i << endl; // Commented part of the code
        if (i == 100)
            break;
        i++;
    }

    // The clock for the time reporting stops
    auto end_time = chrono::high_resolution_clock::now();
    // The duration is calculated in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Duration : " << duration.count() << " milliseconds " << endl;

    return 0;
}
