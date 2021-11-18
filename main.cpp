// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

// do we want headers? eh prob not. 
#include "InversionCounter.cpp";
#include "IntegerMultiplier.cpp";

int main() {

    // debug your alg against these numbers. 
    std::string firstInt = "12";
    std::string secondInt = "45";

    IntegerMultiplier intMultiplier; 
    std::string result = intMultiplier.GradeSchoolMultiplication(firstInt, secondInt);

    std::cout << "Brute force grade school multiplication result: " << result << "\n";

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
