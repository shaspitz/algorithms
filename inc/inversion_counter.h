#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/// <summary>
/// Solves the problem of counting the number of inversions in an array.
/// </summary>
class InversionCounter {
public:
    unsigned long SortAndCountInversions(std::vector<unsigned long>& vector);
    unsigned long BruteForceInvs(std::vector<unsigned long>& vector);
private:
    /// <summary>
    /// Solution structure containing a sorted vector and it's number of split inversions before the sort. 
    /// </summary>
    struct MergeAndCountSolution {
        std::vector<unsigned long> sortedVector;
        unsigned long vectorSplitInversions = -1;
    };
    MergeAndCountSolution MergeAndCountInversions(std::vector<unsigned long>& lowerSplit, std::vector<unsigned long>& upperSplit);
};


