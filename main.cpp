// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

// do we want headers? eh prob not. 
#include "InversionCounter.cpp";

int main() {

    InversionCounter inversionCounter;
    
    std::vector<int> vec = { 5, 4, 3, 2, 1, 5, 3, 7, 89, 43, 324, 5345, 12, 5, 75, 645, 7, 345, 234, 5, };

    // brute force. O(N^2)
    int numInv = inversionCounter.BruteForceInvs(vec);
    std::cout << "brute force: " << numInv << "\n";


    // time complexity of O(N * log(n))
    numInv = inversionCounter.SortAndCountInversions(vec);
    std::cout << "merge sort: " << numInv;

    return 0;
}
