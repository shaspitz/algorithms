#include "../inc/integer_multiplier.h"

/// <summary>
/// Multiplies two integers stored as strings in O(n^2) time. 
/// Assumes the two ints are the same length and contain only numbers. 
/// </summary>
/// <param name="firstInt"></param>
/// <param name="secondInt"></param>
/// <returns></returns>
std::string IntegerMultiplier::GradeSchoolMultiplication(const std::string& topInt, const std::string& bottomInt) {

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
std::string IntegerMultiplier::KaratsubaMultiply(const std::string& firstInt, const std::string& secondInt) {
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

/// <summary>
/// Recursive method to add integer value to string and carry over digits when neccessary. 
/// </summary>
/// <param name="stringByRef"></param>
/// <param name="index"></param>
/// <param name="value"></param>
void IntegerMultiplier::AddValueToString(std::string& stringByRef, auto index, auto value) {
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

/// <summary>
///	Mathematically adds two input integers represented as strings.  
/// </summary>
/// <param name="firstInt"></param>
/// <param name="secondInt"></param>
/// <returns></returns>
std::string IntegerMultiplier::AddIntStrings(std::string firstInt, std::string secondInt) {
	int carryOver = 0;
	int intResult = 0;
	std::string strResult;
	std::string returnResult;
	PadWithZeros(firstInt, secondInt);
	for (auto i = 0; i < firstInt.size(); i++) {
		intResult = firstInt[firstInt.size() - i - 1] - '0' + secondInt[secondInt.size() - i - 1] - '0' + carryOver;
		carryOver = 0;
		if (intResult > 9) {
			carryOver = 1;
			intResult -= 10;
		}
		strResult.push_back(intResult + '0');
	}
	if (carryOver == 1) strResult.push_back('1');
	for (auto i = 0; i < strResult.size(); i++) {
		returnResult.push_back(strResult[strResult.size() - i - 1]);
	}
	auto pos = returnResult.find_first_not_of('0');
	if (pos != std::string::npos) returnResult = returnResult.substr(pos, returnResult.size() - pos);
	else returnResult = '0';
	return returnResult;
}

/// <summary>
/// Mathematically subtracts two input integers represented as strings. 
/// TODO: combine with above method to reduce repeated code. 
/// </summary>
/// <param name="firstInt"></param>
/// <param name="secondInt"></param>
/// <returns></returns>
std::string IntegerMultiplier::SubtractIntStrings(std::string firstInt, std::string secondInt) {
	int carryOver = 0;
	int intResult = 0;
	std::string strResult;
	std::string returnResult;
	PadWithZeros(firstInt, secondInt);
	for (int i = 0; i < firstInt.size(); i++) {
		intResult = firstInt[firstInt.size() - i - 1] - secondInt[secondInt.size() - i - 1] - carryOver;
		carryOver = 0;
		if (intResult < 0) {
			carryOver = 1;
			intResult += 10;
		}
		strResult.push_back(intResult + '0');
	}
	for (int i = 0; i < strResult.size(); i++) {
		returnResult.push_back(strResult[strResult.size() - i - 1]);
	}
	int pos = returnResult.find_first_not_of('0');
	if (pos != std::string::npos) returnResult = returnResult.substr(pos, returnResult.size() - pos);
	else returnResult = '0';
	return returnResult;
}

/// <summary>
/// Pads firstInt and secondInt with zeros for subsequent additions or subtractions.
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
void IntegerMultiplier::PadWithZeros(std::string& firstInt, std::string& secondInt) {
	auto firstLen = firstInt.size();
	auto secondLen = secondInt.size();
	if (firstLen > secondLen) {
		for (auto i = 0; i < firstLen - secondLen; i++) {
			secondInt = ('0' + secondInt);
		}
	}
	else {
		for (auto i = 0; i < secondLen - firstLen; i++) {
			firstInt = ('0' + firstInt);
		}
	}
}

/// <summary>
/// Mathematically multiplies the baseValue integer (rep as string) by a power of ten specified by exponentValue. 
/// </summary>
/// <param name="baseValue"></param>
/// <param name="exponentValue"></param>
/// <returns></returns>
std::string IntegerMultiplier::PowerOfTenAsString(std::string baseValue, auto exponentValue) {
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
std::pair<std::string, std::string> IntegerMultiplier::SplitInteger(std::string inputInt) {
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
size_t IntegerMultiplier::VerifyNumLength(const std::string& firstInt, const std::string& secondInt) {
	auto length = firstInt.size();
	if (length != secondInt.size())
		throw std::invalid_argument("Integers are assumed to be of same length.");
	return length;
}
