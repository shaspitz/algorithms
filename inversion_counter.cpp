#include "inversion_counter.h"

/// <summary>
/// Sorts an entire array and returns its total number of inversions in O(n * log(n)).
/// </summary>
/// <param name="vector">Passed by reference to be sorted.</param>
/// <returns></returns>
unsigned long InversionCounter::SortAndCountInversions(std::vector<unsigned long>& vector) {
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
	auto sol = MergeAndCountInversions(lowerSplit, upperSplit);
	// we can do better here rather than returning a new vector.
	vector = sol.sortedVector;

	return lowerInversions + upperInversions + sol.vectorSplitInversions;
}

/// <summary>
/// Iterate through each value in the array and check how many values are less than current one.
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
unsigned long InversionCounter::BruteForceInvs(std::vector<unsigned long>& vector) {
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
std::vector<unsigned long> InversionCounter::parseTextFile(const std::string& nameTextFile) {
	std::ifstream stream{ nameTextFile };

	if (!stream) {
		throw "Error instantiating ifstram for parsing text file";
	}

	// TODO: use arrays and templates throughout this entire class,
	// since the length of the text file is known. We can at least preallocate. 
	std::vector<unsigned long> returnVec;
	returnVec.reserve(100000);
	unsigned long row;
	while (stream >> row) {
		returnVec.push_back(row);
	}
	return returnVec;
};

/// <summary>
/// Merges and sorts two given arrays, assuming those arrays are sorted. Also returns number of split inversions.
/// </summary>
/// <param name="lowerSplit"></param>
/// <param name="upperSplit"></param>
/// <returns></returns>
InversionCounter::MergeAndCountSolution InversionCounter::MergeAndCountInversions(std::vector<unsigned long>& lowerSplit, std::vector<unsigned long>& upperSplit) {
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

