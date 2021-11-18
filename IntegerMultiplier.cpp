
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

/// <summary>
/// Algorithms for integer multiplication. 
/// Uses strings since integers given in problem statement exceed length of what can be hardcoded in C++. 
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

		auto length = GetLength(topInt, bottomInt);

		// Odd, but I'm going to do it this way lol.
		std::vector<int> results(2 * length, 0);
		for (int bottomCounter = length - 1; bottomCounter >= 0; --bottomCounter) {
			for (int topCounter = length - 1; topCounter >= 0; --topCounter) {
				auto interProduct = topInt[topCounter] * bottomInt[bottomCounter];
				results[bottomCounter + topCounter] += interProduct;
			}
		}
		
		std::string returnString;
		int resCount = 0;
		for (int result : results) {
			int digitCount = 0;
			while (result != 0) {
				auto remainder = result % 10;
				AddValueToString(returnString, resCount + digitCount, remainder);
				++digitCount;
				result /= 10;
			}
			++resCount;
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
			char charValue = static_cast<char>(value);
			stringByRef += charValue;
		}
		else {
			// Value already exists at index. 
			int currentValue = static_cast<int>(stringByRef[index]);
			int newValue = currentValue + value;
			stringByRef[index] = newValue % 10;
			if (newValue / 10 != 0)
				// Carry over. 
				AddValueToString(stringByRef, index + 1, newValue / 10);
		}
	}

	size_t GetLength(const std::string& firstInt, const std::string& secondInt) {
		auto length = firstInt.size();
		if (length != secondInt.size()) throw std::invalid_argument("Integers are assumed to be of same length.");
		return length;
	}
};
