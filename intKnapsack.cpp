#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

/*
Name: Christopher Bingham
Email: cbingha2@binghamton.edu
Assignment: Week 10 - Integer Knapsack
*/

class Items {
    /*
    Class to store relevant data for DP Integer Knapsack
    numItems <int>: Number of items to keep track of
    sackWeight <int>: Max weight of sack to fill
    values <vector<int>>: Array of the items' values
    weights <vector<int>>: Array of the items' weights
    dpTable <vector<vector<int>>>: Dynamic Programming Table
    */
    public:
        int numItems;
        int sackWeight;
        vector<int> values;
        vector<int> weights;
        vector<vector<int>> dpTable;

};

void printItemWeightPair(Items &itemList) {
    /*
    Print out each item value/weight pair
    Parameters:
        itemList <&Items>: Object that contains all values and weights
    Returns:
        None
    */
    for(int i = 0; i < itemList.numItems + 1; i++){
        cout << "Item # " << i << " | Value: " << itemList.values[i] << "| Weight: " << itemList.weights[i] << endl;
    }
    return;
}

void printDPTable(Items &itemList) {
    /*
    Print out the DP Table to visually see the matrix
    Parameters:
        itemList <&Item>: Contains the DP table within the class
    Returns:
        None
    */
    for (int i = 0; i < itemList.numItems + 1; i++) {
        for (int j = 0; j < itemList.sackWeight + 1; j++) {
            cout << itemList.dpTable[i][j] << "\t|\t";
        }
        cout << endl;
    }
    return;
}


void readFile(ifstream &inputFile, Items &itemList) {
    /*
    Read the file data and initialize the data for the Integer Knapsack problem
    Parameters:
        inputFile <&ifstream>: File to read sack information from
        itemList <&itemList>: Stores the values and weights of each respecitve item
        sackWeight <&int>: Weight of the bag to fill
    Returns:
        None
    */
    inputFile >> itemList.numItems;
    inputFile >> itemList.sackWeight;

    itemList.values.resize(itemList.numItems + 1, 0);
    itemList.weights.resize(itemList.numItems + 1, 0);
    itemList.dpTable.resize(itemList.numItems + 1, vector<int>(itemList.sackWeight + 1, 0));

    int itemValue;
    int itemWeight;
    for(int i = 1; i < itemList.numItems + 1; i++) {
        inputFile >> itemWeight;
        inputFile >> itemValue;
        itemList.values[i] = itemValue;
        itemList.weights[i] = itemWeight; 
    }
    return;
}

void intKnapSack(Items &itemList){
    /*
    Perform the Integer Knapsack through iterating a Dynamic Programming Table
    Parameters:
        itemList <&Items>: Contains the DP table we update throughout the process
    Returns:
        None
    */
    for(int iValue = 1; iValue <= itemList.numItems; iValue++){
        for(int jWeight = 1; jWeight <= itemList.sackWeight; jWeight++){
            if (jWeight >= itemList.weights[iValue]) {
                int leftValue = itemList.dpTable[iValue - 1][jWeight];
                int diagValueSum = itemList.dpTable[iValue - 1][jWeight - itemList.weights[iValue]] + itemList.values[iValue];
                itemList.dpTable[iValue][jWeight] = max(leftValue, diagValueSum);
            }
            else {
                itemList.dpTable[iValue][jWeight] = itemList.dpTable[iValue - 1][jWeight];
            }
        }

    }
    return;
}

void printItemsMaxValue(Items &itemList) {
    /*
    Print out the maximum value for the sack and the path that led to the solution
    Parameters:
        itemList <&Items>: Contains the DP table containing the solved knapsack
    Returns:
        None
    */
    int maxVal = itemList.dpTable[itemList.numItems][itemList.sackWeight];

    // cout << "Maximum Knapsack Value: " << maxVal << endl;
    cout << maxVal << endl;

    int shiftWeight = itemList.sackWeight;
    for(int i = itemList.numItems; i > 0 && maxVal > 0; i--) {
        if (maxVal != itemList.dpTable[i - 1][shiftWeight]) {
            // cout << "Item # " << i << " | Value: " << itemList.values[i] << "| Weight: " << itemList.weights[i] << endl;
            cout << itemList.weights[i] << " " << itemList.values[i] << endl;

            maxVal -= itemList.values[i];
            shiftWeight -= itemList.weights[i];
        }
    }

}

int main(int argc, char *argv[]) {
    /*
    Main function to execute the Integer Knapsack algorithm.
    CommandLine Usage:
        - ./rodCut <input_file>
    Command line arguments:
        - argv[1]: The name of the input file
        - If no command line argument is provided, the user will be prompted to enter the file name.
    Returns:
        - 0: Successful execution
        - 1: Error in opening the input file
    */

    //Read the input file and build the vertices and edges
    ifstream inputFile;
    Items itemList;

    if (argc != 2) {
        string fileName;
        cout << "Enter File Name: " << endl;
        cin >> fileName;
        inputFile.open(fileName);
    } else {
        inputFile.open(argv[1]);
    }

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    readFile(inputFile, itemList);

    //Uncomment to see the Value/Weight Pairs
    // printItemWeightPair(itemList);

    intKnapSack(itemList);

    //Uncomment to see the whole DP Table
    // printDPTable(itemList);

    printItemsMaxValue(itemList);


    return 0;
}