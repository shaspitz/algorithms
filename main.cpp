// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

// do we want headers? eh prob not. 
#include "InversionCounter.cpp";

int main() {
    InversionCounter inversionCounter;
    
    // Dealing with large numbers here, all ints will be represented as usigned longs to prevent overflow or wraparound.
    std::vector<unsigned long> testVec = { 5, 4, 3, 2, 1, 5, 3, 7, 89, 43, 324, 5345, 12, 5, 75, 645, 7, 345, 234, 5, };

    // Brute force, O(N^2).
    unsigned long numInv = inversionCounter.BruteForceInvs(testVec);
    std::cout << "Brute force solution, number of inversions in test vec: " << numInv << "\n";

    // Count inversions using merge sort, time complexity of O(N * log(n)).
    numInv = inversionCounter.SortAndCountInversions(testVec);
    std::cout << "Merge sort solution, number of inversions in test vec: " << numInv << "\n";

    std::vector<unsigned long> textVec = inversionCounter.parseTextFile("IntegerArray.txt");
    std::cout << "Merge sort solution, number of inversions in text file: " << inversionCounter.SortAndCountInversions(textVec) << "\n";
    return 0;
}
