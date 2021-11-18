
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

/// <summary>
/// Algorithms for integer multiplication. 
/// Uses strings due to the size of integers we're testing against. 
/// </summary>
class IntegerMultiplier {
public:

	// TODO: implement karutsuba or generic recursive, potentially with gausses trick. 


	/// <summary>
	/// Multiplies two integers stored as strings in O(n^2) time. 
	/// Assumes the two ints are the same length and contain only numbers. 
	/// </summary>
	/// <param name="firstInt"></param>
	/// <param name="secondInt"></param>
	/// <returns></returns>
	std::string GradeSchoolMultiplication(const std::string& topInt, const std::string& bottomInt) {

		auto length = GetNumLength(topInt, bottomInt);

		// Results will hold values of any number of digits, where position in array 
		// denotes the power of ten for each multiplication result. 
		std::vector<int> results(2 * length, 0);
		for (int bottomCounter = length - 1; bottomCounter >= 0; --bottomCounter) {
			for (int topCounter = length - 1; topCounter >= 0; --topCounter) {
				auto interProduct = (topInt[topCounter] - '0') * (bottomInt[bottomCounter] - '0'); // Hanlde ASCII.
				auto resultsCounter = bottomCounter + topCounter + 1;
				results[resultsCounter] += interProduct;
			}
		}

		// Iterate through the results vector backwards to add values to each index appropriately. 
		std::string returnString;
		for (int resCount = results.size() - 1; resCount >= 0; --resCount) {
			int digitCount = 0;
			while (results[resCount] != 0) {
				auto remainder = results[resCount] % 10;
				// We'll add values to the return string forwards, then will reverse values at end for final answer.
				auto reverseIndex = results.size() - 1 - resCount + digitCount;
				AddValueToString(returnString, reverseIndex, remainder);
				++digitCount;
				results[resCount] /= 10;
			}
		}
	
		std::reverse(returnString.begin(), returnString.end());
		return returnString;
	}

private: 
	/// <summary>
	/// Recursive method to add integer value to string and carry over digits when neccessary. 
	/// </summary>
	/// <param name="stringByRef"></param>
	/// <param name="index"></param>
	/// <param name="value"></param>
	void AddValueToString(std::string& stringByRef, int index, int value) {
		if (value / 10 != 0 || value < 0)
			throw std::invalid_argument("Value to add must be single digit and positive.");
		if (stringByRef.size() <= index) {
			auto strValue = std::to_string(value);
			stringByRef.push_back(*strValue.begin());
		}
		else {
			// Value already exists at index. 
			auto currentValue = stringByRef[index] - '0'; // Subtract ASCII 48.
			int newValue = currentValue + value;
			stringByRef[index] = *std::to_string(newValue % 10).begin();
			if (newValue / 10 != 0)
				// Carry over to next digit. 
				AddValueToString(stringByRef, index + 1, newValue / 10);
		}
	}

	size_t GetNumLength(const std::string& firstInt, const std::string& secondInt) {
		auto length = firstInt.size();
		if (length != secondInt.size())
			throw std::invalid_argument("Integers are assumed to be of same length.");
		return length;
	}
};
