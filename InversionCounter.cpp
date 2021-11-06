
#include <vector>
#include <iostream>


// TODO: make headers and pretty this up.

// TODO: make a base class so that all solutions can be called from a driver. 

// TODO: also (re) code up the solution to assignment #1 for github.  

// TODO: just use similar coding style to work, even if that's .NET based. Can make a note of that if you'd like. 

// TODO: do this whole thing with arrays? and use the text file. 

// TODO: need to setup the git ignores. 


class InversionCounter {
public: 
    // nums passed by ref! Will be mutated.  
// Sorts an entire array and returns its total number of inversions.
    int SortAndCountInversions(std::vector<int>& nums) {
        // base case, array is already sorted and there are no inversions.
        if (nums.size() == 1)
            return 0;

        // Split array in half using iterators.
        std::size_t const halfSize = nums.size() / 2;
        std::vector<int> lowerSplit(nums.begin(), nums.begin() + halfSize);
        std::vector<int> upperSplit(nums.begin() + halfSize, nums.end());

        // recursively sort array.
        int lowerInversions = SortAndCountInversions(lowerSplit);
        int upperInversions = SortAndCountInversions(upperSplit);

        // total inversions is sum of low, hi and split.
        MergeAndCountSolution sol = MergeAndCountInversions(lowerSplit, upperSplit);
        // we can do better here rather than returning a new vector.
        nums = sol.sortedVector;
        return lowerInversions + upperInversions + sol.numSplitInversions;
    }

    // Go through each value in the array and check how many values after the current one 
    // are less than the current one.
    int BruteForceInvs(std::vector<int>& nums) {
        int invs = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[j] < nums[i])
                    ++invs;
            }
        }
        return invs;
    }

private: 
    // This could apply to both solutions really, or can use references to reduce instantiated vectors. 
    static struct MergeAndCountSolution {
        std::vector<int> sortedVector;
        int numSplitInversions;
    };

    // returns num of split inversions, note that nums is passed by ref! Will be mutated. 
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
        sol.numSplitInversions = splitInv;
        return sol;
    }
};
