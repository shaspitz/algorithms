
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <math.h>

/// <summary>
/// Algorithms for integer multiplication. 
/// Uses strings due to the size of integers we're testing against. 
/// </summary>
class IntegerMultiplier {
public:
	/// <summary>
	/// Multiplies two integers stored as strings in O(n^2) time. 
	/// Assumes the two ints are the same length and contain only numbers. 
	/// </summary>
	/// <param name="firstInt"></param>
	/// <param name="secondInt"></param>
	/// <returns></returns>
	std::string GradeSchoolMultiplication(const std::string& topInt, const std::string& bottomInt) {

		auto length = VerifyNumLength(topInt, bottomInt);

		// Results will hold values of any number of digits, where position in array 
		// denotes the power of ten for each multiplication result. 
		std::vector<int> results(2 * length, 0);
		for (int bottomCounter = (int)length - 1; bottomCounter >= 0; --bottomCounter) {
			for (int topCounter = (int)length - 1; topCounter >= 0; --topCounter) {
				auto interProduct = (topInt[topCounter] - '0') * (bottomInt[bottomCounter] - '0'); // Handle ASCII.
				auto resultsCounter = bottomCounter + topCounter + 1;
				results[resultsCounter] += interProduct;
			}
		}

		// Iterate through the results vector backwards to add values to each index appropriately. 
		std::string returnString;
		for (int resCount = (int)results.size() - 1; resCount >= 0; --resCount) {
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

	/// <summary>
	/// Multiply two integers using the karatsuba algorithm. 
	/// Time complexity: Using the master method with a = 3 recursive calls, b = 2 as shrinkage factor, 
	/// and d = 1 as exponent of running time of combining step...
	/// T(n) = O(n ^ log2(3)) = O(n ^ 1.59), meaning this has a better time complexity than grade school multiplication,
	/// due to the time savings of having only three recursive calls, where work at the leaves of the recursion tree dominate. 
	/// </summary>
	/// <param name="topInt"></param>
	/// <param name="bottomInt"></param>
	/// <returns></returns>
	std::string KaratsubaMultiply(const std::string& firstInt, const std::string& secondInt) {
		// Recall that x * y = 10^n * a * c + 10^(n/2) * (a * d + b * c) + b * d,
		// where a, b, c, d are n/2 digit numbers representing the first and second halfs of each int.
		
		// Base case.
		if (firstInt.length() == 1 || secondInt.length() == 1) {
			int firstIntAsInt = std::stoi(firstInt);
			int secondIntAsInt = std::stoi(secondInt);
			return std::to_string(firstIntAsInt * secondIntAsInt);
		}

		auto [a, b] = SplitInteger(firstInt);
		auto [c, d] = SplitInteger(secondInt);

		auto ac = KaratsubaMultiply(a, c);
		auto bd = KaratsubaMultiply(b, d);

		// Gauss's trick.
		auto aPlusBTimesCPlusD = KaratsubaMultiply(AddIntStrings(a, b), AddIntStrings(c, d));
		auto aDPlusBC = SubtractIntStrings(SubtractIntStrings(aPlusBTimesCPlusD, ac), bd); 

		return AddIntStrings(PowerOfTenAsString(ac, firstInt.size()),
			AddIntStrings(PowerOfTenAsString(aDPlusBC, firstInt.size() / 2), bd));
	}

private: 
	/// <summary>
	/// Recursive method to add integer value to string and carry over digits when neccessary. 
	/// </summary>
	/// <param name="stringByRef"></param>
	/// <param name="index"></param>
	/// <param name="value"></param>
	void AddValueToString(std::string& stringByRef, auto index, auto value) {
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

	std::string AddIntStrings(std::string firstInt, std::string secondInt) {
		int carrier = 0;
		int bitresult = 0;
		std::string fullResult;
		std::string finalResult;
		PadWithZeros(firstInt, secondInt);
		for (auto i = 0; i < firstInt.size(); i++) {
			bitresult = firstInt[firstInt.size() - i - 1] - '0' + secondInt[secondInt.size() - i - 1] - '0' + carrier;
			carrier = 0;
			if (bitresult > 9) {
				carrier = 1;
				bitresult = bitresult - 10;
			}
			fullResult.push_back(bitresult + '0');
		}
		if (carrier == 1)fullResult.push_back('1');
		for (auto i = 0; i < fullResult.size(); i++) {
			finalResult.push_back(fullResult[fullResult.size() - i - 1]);
		}
		auto pos = finalResult.find_first_not_of('0');
		if (pos != std::string::npos)finalResult = finalResult.substr(pos, finalResult.size() - pos);
		else finalResult = '0';
		return finalResult;
	}

	/// <summary>
	/// TODO: combine with above method to reduce repeated code. 
	/// </summary>
	/// <param name="firstInt"></param>
	/// <param name="secondInt"></param>
	/// <returns></returns>
	std::string SubtractIntStrings(std::string firstInt, std::string secondInt) {
		int carrier = 0;
		int bitresult = 0;
		std::string fullResult;
		std::string finalResult;
		PadWithZeros(firstInt, secondInt);
		for (int i = 0; i < firstInt.size(); i++) {
			bitresult = firstInt[firstInt.size() - i - 1] - secondInt[secondInt.size() - i - 1] - carrier;
			carrier = 0;
			if (bitresult < 0) {
				carrier = 1;
				bitresult = bitresult + 10;
			}
			fullResult.push_back(bitresult + '0');
		}
		for (int i = 0; i < fullResult.size(); i++) {
			finalResult.push_back(fullResult[fullResult.size() - i - 1]);
		}
		int pos = finalResult.find_first_not_of('0');
		if (pos != std::string::npos)finalResult = finalResult.substr(pos, finalResult.size() - pos);
		else finalResult = '0';
		return finalResult;
	}

	void PadWithZeros(std::string& num1, std::string& num2) {
		auto l1 = num1.size();
		auto l2 = num2.size();
		if (l1 > l2) {
			for (auto i = 0; i < l1 - l2; i++) {
				num2 = ('0' + num2);
			}
		}
		else {
			for (auto i = 0; i < l2 - l1; i++) {
				num1 = ('0' + num1);
			}
		}
	}

	std::string PowerOfTenAsString(std::string baseValue, auto exponentValue) {
		for (auto i = 0; i < exponentValue; ++i) {
			baseValue += '0';
		}
		return baseValue;
	}

	/// <summary>
	/// Splits an input integer (as string) into the first half of it's digits and the second half of it's digits. 
	/// </summary>
	/// <param name="inputInt"></param>
	/// <returns>A pair of strings denoting the first and second half of digits from the input integer.</returns>
	std::pair<std::string, std::string> SplitInteger(std::string inputInt) {
		auto length = inputInt.size();
		std::pair<std::string, std::string> returnPair(inputInt.substr(0, length / 2), inputInt.substr(length / 2));
		return returnPair;
	}

	/// <summary>
	/// Get's length of the two input integers (as string) and ensures they're the same length. 
	/// </summary>
	/// <param name="firstInt"></param>
	/// <param name="secondInt"></param>
	/// <returns>Length of two integers.</returns>
	size_t VerifyNumLength(const std::string& firstInt, const std::string& secondInt) {
		auto length = firstInt.size();
		if (length != secondInt.size())
			throw std::invalid_argument("Integers are assumed to be of same length.");
		return length;
	}
};

