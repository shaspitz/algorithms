#include "../inc/integer_multiplier.h"
#include "../inc/inversion_counter.h"
#include "../inc/quick_sorter.h"

namespace Helpers {
	/// <summary>
	/// Parse text file for integers separated by newlines.
	/// </summary>
	/// <param name="nameTextFile"></param>
	/// <returns></returns>
	std::vector<unsigned long> ParseTextFile(const std::string& nameTextFile, int arraySize) {
		std::ifstream stream{ nameTextFile };

		if (!stream) {
			throw "Error instantiating ifstram for parsing text file";
		}

		// TODO: use arrays and templates throughout this entire class,
		// since the length of the text file is known. We can at least preallocate. 
		std::vector<unsigned long> returnVec;
		returnVec.reserve(arraySize);
		unsigned long row;
		while (stream >> row) {
			returnVec.push_back(row);
		}
		return returnVec;
	};
}

int main() {
    try {
		// Numbers given in problem statement. 
		std::string firstInt = "3141592653589793238462643383279502884197169399375105820974944592";
		std::string secondInt = "2718281828459045235360287471352662497757247093699959574966967627";

		IntegerMultiplier intMultiplier; 

		auto gradeSchoolRes = intMultiplier.GradeSchoolMultiplication(firstInt, secondInt);
		std::cout << "Brute force grade school multiplication result: " << gradeSchoolRes << "\n";

		auto karatsubaRes = intMultiplier.KaratsubaMultiply(firstInt, secondInt);
		std::cout << "Karatsuba multiplication result: " << karatsubaRes << "\n";

		InversionCounter inversionCounter;
		
		// Dealing with large numbers here, all ints will be represented as usigned longs to prevent overflow or wraparound.
		std::vector<unsigned long> testVec = { 5, 4, 3, 2, 1, 5, 3, 7, 89, 43, 324, 5345, 12, 5, 75, 645, 7, 345, 234, 5, };

		// Brute force, O(N^2).
		unsigned long numInv = inversionCounter.BruteForceInvs(testVec);
		std::cout << "Brute force solution, number of inversions in test vec: " << numInv << "\n";

		// Count inversions using merge sort, time complexity of O(N * log(n)).
		numInv = inversionCounter.SortAndCountInversions(testVec);
		std::cout << "Merge sort solution, number of inversions in test vec: " << numInv << "\n";

		std::vector<unsigned long> mergeSortVector = Helpers::ParseTextFile("IntegerArray.txt", 100000);
		std::cout << "Merge sort solution, number of inversions in text file: " << inversionCounter.SortAndCountInversions(mergeSortVector) << "\n";

		std::vector<unsigned long> quickSortVector = Helpers::ParseTextFile("QuickSort.txt", 10000);
		QuickSorter quickSorter;
		std::cout << "Number of comparisons in quick sort, always choosing first element as pivot: "
			<< quickSorter.QuickSort(quickSortVector, QuickSorter::PivotMethod::ChooseFirst) << "\n";
		std::cout << "Number of comparisons in quick sort, always choosing last element as pivot: "
			<< quickSorter.QuickSort(quickSortVector, QuickSorter::PivotMethod::ChooseLast) << "\n";
		std::cout << "Number of comparisons in quick sort, choosing median of three element as pivot: "
			<< quickSorter.QuickSort(quickSortVector, QuickSorter::PivotMethod::ChooseMedianOfThree) << "\n";

		// Testing!!! Coursera says I'm wrong. Maybe try the brute force partition? 
		std::vector<unsigned long> test{ 4, 5, 6, 7, 8, 9, };
		std::cout << "Number of comparisons in quick sort, choosing median of three element as pivot: "
			<< quickSorter.QuickSort(test, QuickSorter::PivotMethod::ChooseMedianOfThree) << "\n";

	} catch (const std::exception& ex) {
		std::cout << "\n" << "std::exception thrown: " << ex.what() << "\n";
	} catch (const std::string& ex) {
		std::cout << "\n" << "string thrown: " << ex << "\n";
	} catch (...) {
		std::cout << "\n" << "Unknown exception type" << "\n";
	}
   return 0;
}



