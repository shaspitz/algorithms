#include "../integer_multiplier.h"
#include "../inversion_counter.h"

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

		std::vector<unsigned long> textVec = inversionCounter.parseTextFile("IntegerArray.txt");
		std::cout << "Merge sort solution, number of inversions in text file: " << inversionCounter.SortAndCountInversions(textVec) << "\n";
	 
	} catch (const std::exception& ex) {
		std::cout << "\n" << "std::exception thrown: " << ex.what() << "\n";
	} catch (const std::string& ex) {
		std::cout << "\n" << "string thrown: " << ex << "\n";
	} catch (...) {
		std::cout << "\n" << "Unknown exception type" << "\n";
	}
   return 0;
}

