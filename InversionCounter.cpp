
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


// TODO: make headers and pretty this up.

// TODO: make a base class so that all solutions can be called from a driver. 

// TODO: also (re) code up the solution to assignment #1 for github.  

// TODO: just use similar coding style to work, even if that's .NET based. Can make a note of that if you'd like. 

// TODO: do this whole thing with arrays? and use the text file. 

// TODO: need to setup the git ignores. 


class InversionCounter {
public: 
    // vector passed by ref! Will be mutated.  
// Sorts an entire array and returns its total number of inversions.
    int SortAndCountInversions(std::vector<int>& vector) {
        // base case, array is already sorted and there are no inversions.
        if (vector.size() == 1)
            return 0;

        // Split array in half using iterators.
        std::size_t const halfSize = vector.size() / 2;
        std::vector<int> lowerSplit(vector.begin(), vector.begin() + halfSize);
        std::vector<int> upperSplit(vector.begin() + halfSize, vector.end());

        // recursively sort array.
        int lowerInversions = SortAndCountInversions(lowerSplit);
        int upperInversions = SortAndCountInversions(upperSplit);

        // total inversions is sum of low, hi and split.
        MergeAndCountSolution sol = MergeAndCountInversions(lowerSplit, upperSplit);
        // we can do better here rather than returning a new vector.
        vector = sol.sortedVector;
        return lowerInversions + upperInversions + sol.vectorplitInversions;
    }

    // Go through each value in the array and check how many values after the current one 
    // are less than the current one.
    int BruteForceInvs(std::vector<int>& vector) {
        int invs = 0;
        for (int i = 0; i < vector.size() - 1; ++i) {
            for (int j = i + 1; j < vector.size(); ++j) {
                if (vector[j] < vector[i])
                    ++invs;
            }
        }
        return invs;
    }

    std::vector<int> parseTextFile(const std::string& nameTextFile){
        std::ifstream stream { nameTextFile };

        if (!stream) {
            throw "Nooooooo";
        }

        std::vector<int> returnVec;
        int row;
        while (stream >> row) {
            returnVec.push_back(row);

        }
        /// Efficient enough to return by value.
        return returnVec;
    };

private: 
    // This could apply to both solutions really, or can use references to reduce instantiated vectors. 
    static struct MergeAndCountSolution {
        std::vector<int> sortedVector;
        int vectorplitInversions;
    };

    // returns num of split inversions, note that vector is passed by ref! Will be mutated. 
    // Merges and sorts two given arrays, assuming those arrays are sorted. Also returns number of split inversions.
    MergeAndCountSolution MergeAndCountInversions(std::vector<int>& lowerSplit, std::vector<int>& upperSplit) {

        // divide and conquer, merge sort!

        MergeAndCountSolution sol;
        int lowerCounter = 0; int upperCounter = 0; int splitInv = 0;

        // Do we need parathesese around the sizes here?
        for (int k = 0; k < lowerSplit.size() + upperSplit.size(); ++k) {
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
                splitInv += lowerSplit.size() - lowerCounter;
            }
        }
        sol.vectorplitInversions = splitInv;
        return sol;
    }
};
