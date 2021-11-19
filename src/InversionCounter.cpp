
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

// TODO: make headers and pretty this up.

// TODO: make a section in the readme of this project that states all the possible optimizations you can make for the code.
// Biggest example here is using a template and arrays to read data from the text file. 

// TODO: Code up the shortest distance algorithm from week 2 optional videos, closest split pair

// TODO: just use similar coding style to work, even if that's .NET based. Can make a note of that if you'd like. 

/// <summary>
/// Solves the problem of counting the number of inversions in an array in O(n * log(n)). 
/// </summary>
class InversionCounter {
public: 
    /// <summary>
    /// Sorts an entire array and returns its total number of inversions.
    /// </summary>
    /// <param name="vector">Passed by reference to be sorted.</param>
    /// <returns></returns>
    unsigned long SortAndCountInversions(std::vector<unsigned long>& vector) {
        // base case, array is already sorted and there are no inversions.
        if (vector.size() == 1)
            return 0;

        // Divide and conquer! Split array in half using iterators.
        std::size_t const halfSize = vector.size() / 2;
        std::vector<unsigned long> lowerSplit(vector.begin(), vector.begin() + halfSize);
        std::vector<unsigned long> upperSplit(vector.begin() + halfSize, vector.end());

        // recursively sort array.
        unsigned long lowerInversions = SortAndCountInversions(lowerSplit);
        unsigned long upperInversions = SortAndCountInversions(upperSplit);

        // total inversions is sum of low, hi and split.
        MergeAndCountSolution sol = MergeAndCountInversions(lowerSplit, upperSplit);
        // we can do better here rather than returning a new vector.
        vector = sol.sortedVector;
        
        return lowerInversions + upperInversions + sol.vectorSplitInversions;
    }

    /// <summary>
    /// Iterate through each value in the array and check how many values are less than current one.
    /// </summary>
    /// <param name="vector"></param>
    /// <returns></returns>
    unsigned long BruteForceInvs(std::vector<unsigned long>& vector) {
        unsigned long invs = 0;
        for (unsigned long i = 0; i < vector.size() - 1; ++i) {
            for (unsigned long j = i + 1; j < vector.size(); ++j) {
                if (vector[j] < vector[i])
                    ++invs;
            }
        }
        return invs;
    }

    /// <summary>
    /// Parse text file for integers separated by newlines.
    /// </summary>
    /// <param name="nameTextFile"></param>
    /// <returns></returns>
    std::vector<unsigned long> parseTextFile(const std::string& nameTextFile){
        std::ifstream stream { nameTextFile };

        if (!stream) {
            throw "Nooooooo";
        }

        std::vector<unsigned long> returnVec;
        unsigned long row;
        while (stream >> row) {
            returnVec.push_back(row);
        }
        return returnVec;
    };

private: 
    /// <summary>
    /// Solution structure containing a sorted vector and it's number of split inversions before the sort. 
    /// TODO: Replace this by not instantiating a new vector. 
    /// </summary>
    struct MergeAndCountSolution {
        std::vector<unsigned long> sortedVector;
        unsigned long vectorSplitInversions = -1;
    };

    /// <summary>
    /// Merges and sorts two given arrays, assuming those arrays are sorted. Also returns number of split inversions.
    /// </summary>
    /// <param name="lowerSplit"></param>
    /// <param name="upperSplit"></param>
    /// <returns></returns>
    MergeAndCountSolution MergeAndCountInversions(std::vector<unsigned long>& lowerSplit, std::vector<unsigned long>& upperSplit) {
        MergeAndCountSolution sol;
        unsigned long lowerCounter = 0; unsigned long upperCounter = 0; unsigned long splitInv = 0;

        for (unsigned long k = 0; k < lowerSplit.size() + upperSplit.size(); ++k) {
            // check if lower vec has already been fully iterated through.
            if (lowerCounter == lowerSplit.size()) {
                sol.sortedVector.push_back(upperSplit[upperCounter]);
                ++upperCounter;
            }
            // check if higher vec has already been fully iterated through.
            else if (upperCounter == upperSplit.size()) {
                sol.sortedVector.push_back(lowerSplit[lowerCounter]);
                ++lowerCounter;
            }
            else if (lowerSplit[lowerCounter] <= upperSplit[upperCounter]) {
                sol.sortedVector.push_back(lowerSplit[lowerCounter]);
                ++lowerCounter;
            }
            else {
                sol.sortedVector.push_back(upperSplit[upperCounter]);
                ++upperCounter;
                // This is the very specific case that an inversion is present.
                // # split inversions is how many values are in the left arry,
                // when a value from the right array is less than the most left
                // value in the left array (and implicitly, the value in the right
                // array is less than all the values in the left array since arrays are sorted).
                // Increment the inversion counter accordingly.
                splitInv += (unsigned long)lowerSplit.size() - lowerCounter;
            }
        }
        sol.vectorSplitInversions = splitInv;
        return sol;
    }
};
